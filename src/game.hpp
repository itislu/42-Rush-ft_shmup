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

#define MAX_ENEMIES 100
#define MAX_BULLETS 100

#define KEY_ESCAPE 27

#define COLOR_ORANGE 100

#define FPS 60

#define UP {0, -1}
#define DOWN {0, 1}
#define RIGHT {1, 0}
#define LEFT {-1, 0}

#define ENEMY_1_POINTS 5
#define BASIC_ENEMY_POINTS 10
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
	std::vector<Entity>	collidables;
	Background	background;
};

int shared_players_hp(Game *game);

//background
//collidables
//levels
//different enemies
//boss
//invis frame flash
//game over/game ending
//score
//resize
