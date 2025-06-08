#pragma once

#include "libft/libft.h"
#include "background.hpp"
#include "coordinate.hpp"
#include "time.hpp"
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define GAME_WINDOW_HEIGHT 21
#define GAME_WINDOW_WIDTH 61
#define GAME_WINDOW_Y 3
#define GAME_WINDOW_X 0

#define STATUS_WINDOW_HEIGHT 3
#define STATUS_WINDOW_WIDTH 61
#define STATUS_WINDOW_Y 0
#define STATUS_WINDOW_X 0

#define MAX_MAP_HEIGHT 19
#define MAX_MAP_WIDTH 29

#define MAX_ENEMIES 100
#define MAX_BULLETS 100

#define KEY_ESCAPE 27
#define KEY_SPACE 32

#define FPS 60

#define UP {0, -1}
#define DOWN {0, 1}
#define RIGHT {1, 0}
#define LEFT {-1, 0}

#define ENEMY_1_POINTS 5
#define BASIC_ENEMY_POINTS 10
#define ENEMY_2_POINTS 30

enum entity_type
{
	PLAYER,
	BASIC_ENEMY,
	ENEMY_1, //real basic enemy, just moves to left and shoots
	ENEMY_2, // shoots homing bullets
	PLAYER_BULLET,
	ENEMY_BULLET,
	ENEMY_1_BULLET,
	HOMING_BULLET,
	COLLIDABLE,
	BOSS,
};

struct window
{
	WINDOW	*win;
	int		height;
	int		width;
	int		pos_y;
	int		pos_x;
};

struct entity
{
	int		type;
	bool	status;
	int		hp;
	int		speed;
	int		damage;
	int		direction; //for homing bullets
	long		invis_frames;
	long		shoot_cooldown;
	long		move_cooldown;
	//long		spawn_cooldown;
	std::vector<coordinate>	pattern;
	size_t		pattern_idx;
	coordinate	previous_pos;
	coordinate	current_pos;
};

// struct player : public entity 
// {

// };

// struct enemy : public entity
// {

// };

struct game
{
	WINDOW	*game_win;
	WINDOW	*status_win;
	entity	player;
	long	score;
	long	time;
	long	enemy_spawn_cooldown;
	int		boss_health;
	bool	boss_status;
	long	spawn_boss_cooldown;
	//entity	bullets[MAX_BULLETS];
	/* window	game_win;
	window	status_win;
	entity	player;*/
	std::vector<entity>	enemies;
	std::vector<entity>	bullets;
	std::vector<entity>	collidables;
	background	background;
};

//background
//collidables
//levels
//different enemies
//boss
//invis frame flash
//game over/game ending
//score
//resize
