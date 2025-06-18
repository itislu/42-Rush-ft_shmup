#pragma once

#include "Background.hpp"
#include "Coordinate.hpp"
#include <array>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <vector>

#define MIN_TERMINAL_HEIGHT 20
#define MIN_TERMINAL_WIDTH 50

#define GAME_WINDOW_Y 3
#define GAME_WINDOW_X 0

#define STATUS_WINDOW_Y 0
#define STATUS_WINDOW_X 0
#define STATUS_WINDOW_HEIGHT 3

#define BACKGROUND_SPAWN_COOLDOWN 100
#define BACKGROUND_MOVE_COOLDOWN 80

#define POWERUP_SPAWN_COOLDOWN 10000 //should be more
#define POWERUP_DESPAWN_COOLDOWN 6000
#define POWERUP_DESPAWN_BLINKING 4000
#define POWERUP_ACTIVE_TIME 5000

#define PLAYER_SHOOT_COOLDOWN 200
#define PLAYER_INVIS_FRAMES 1200
#define PLAYER_BULLET_MOVE_COOLDOWN 20

#define ENEMY_SPAWN_COOLDOWN 5000
#define BOSS_SPAWN_COOLDOWN 25000

#define BASIC_ENEMY_MOVE_COOLDOWN 350
#define BASIC_ENEMY_SHOOT_COOLDOWN 1200
#define ENEMY_BULLET_MOVE_COOLDOWN 80

#define ENEMY_1_MOVE_COOLDOWN 300
#define ENEMY_1_SHOOT_COOLDOWN 1500
#define ENEMY_1_BULLET_MOVE_COOLDOWN 100

#define ENEMY_2_MOVE_COOLDOWN 350
#define ENEMY_2_SHOOT_COOLDOWN 2500
#define HOMING_BULLET_MOVE_COOLDOWN 180

#define BOSS_MOVE_COOLDOWN 200
#define BOSS_TRUE_HOMING_BULLET_SHOOT_COOLDOWN 1000
#define BOSS_ENEMY_BULLET_SHOOT_COOLDOWN 200
#define BOSS_ENEMY_BULLET_MOVE_COOLDOWN 50
#define TRUE_HOMING_BULLET_MOVE_COOLDOWN 170

#define KEY_ESCAPE 27

#define COLOR_ORANGE 100

#define FPS 60

#define UP {0, -1}
#define DOWN {0, 1}
#define RIGHT {1, 0}
#define LEFT {-1, 0}

#define BULLET_POINTS 1
#define ENEMY_1_POINTS 10
#define BASIC_ENEMY_POINTS 25
#define ENEMY_2_POINTS 50
#define BOSS_POINTS 1000

extern int map_width;
extern int map_height;

inline const wchar_t  *game_over[] = {
	L"                                        ",
	L"  ███▀▀▀██ ███▀▀▀███ ███▀█▄█▀███ ██▀▀▀  ",
	L"  ██    ██ ██     ██ ██   █   ██ ██     ",
	L"  ██   ▄▄▄ ██▄▄▄▄▄██ ██   ▀   ██ ██▀▀▀  ",
	L"  ██    ██ ██     ██ ██       ██ ██     ",
	L"  ███▄▄▄██ ██     ██ ██       ██ ██▄▄▄  ",
	L"                                        ",
	L"  ███▀▀▀███ ▀███  ██▀ ██▀▀▀ ██▀▀▀▀██▄   ",
	L"  ██     ██   ██  ██  ██    ██     ██   ",
	L"  ██     ██   ██  ██  ██▀▀▀ ██▄▄▄▄▄▀▀   ",
	L"  ██     ██   ██  █▀  ██    ██     ██   ",
	L"  ███▄▄▄███    ▀█▀    ██▄▄▄ ██     ██▄  ",
	L"                                        "
};

enum EntityType
{
	PLAYER,
	BASIC_ENEMY,
	ENEMY_1, //real basic enemy, just moves to left and shoots
	ENEMY_2, // shoots homing bullets
	PLAYER_BULLET,
	ENEMY_BULLET,
	ENEMY_1_BULLET,
	HOMING_BULLET,
	TRUE_HOMING_BULLET,
	COLLIDABLE,
	BOSS,
	EXPLOSION,
	POWERUP_TRIPLE_SHOT,
};

struct Game;

struct Window
{
	WINDOW	*win;
	int		height;
	int		width;
	int		pos_y;
	int		pos_x;
};

struct Entity
{
	int		id;
	int		type;
	bool	status;
	int		hp;
	int		speed;
	int		damage;
	int		direction; //for homing bullets
	int		source; //to know from which enemies the bullets come from (needed for boss to adjust bullet speed)
	long		invis_frames;
	long		shoot_cooldown;
	long		move_cooldown;
	//long		spawn_cooldown;
	std::vector<Coordinate>	pattern;
	size_t		pattern_idx;
	Coordinate	previous_pos;
	Coordinate	current_pos;
};

struct Player : public Entity 
{
	constexpr static int max_players = 2;
	constexpr static std::array<std::array<int, 6>, max_players> controls_sets = 
		{{{'w', 'a', 's', 'd', ' ', 'f'}, 
		  {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, '\n', '-'}}};
	constexpr static std::array<const wchar_t[2], max_players> appearances =
		{{{L"🛸"},
		  {L"🚀"}}};

	Player(int id, Coordinate position);
	bool update(int input, Game *game);
	void shoot(Game *game);
	bool on_collision(Entity *entity, Game *game);
	void print(WINDOW *game_win);
	
	const wchar_t *appearance;
	std::array<int, 6> control_set;
	bool auto_fire_toggle = false;
	int active_powerup = 0;
	long powerup_time = 0;
};

// struct enemy : public Entity
// {

// };

struct Game
{
	Game();

	WINDOW	*game_win = NULL;
	WINDOW	*status_win = NULL;
	int		term_height;
	int		term_width;
	int		game_height;
	int		game_width;
	int		status_height;
	int		status_width;
	std::vector<Player> players;
	long	score = 0;
	long	start_time = 0;
	long	gameover_time = 0;
	long	enemy_spawn_cooldown = 0;
	int		boss_health = 0;
	bool	boss_status = 0;
	long	spawn_boss_cooldown = 0;
	std::vector<Entity>	enemies;
	std::vector<Entity>	bullets;
	std::vector<Entity>	explosions;
	std::vector<Entity>	collidables;
	Background	background;
	Entity		powerup;
	long		powerup_spawn_cooldown = 0;
	long		powerup_despawn_cooldown = 0;
};

int shared_players_hp(Game *game);
void add_explosion(Game *game, Coordinate pos);

//background
//collidables
//levels
//different enemies
//boss
//invis frame flash
//game over/game ending
//score
//resize
