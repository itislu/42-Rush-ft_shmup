#pragma once

#include "../lib/libft/libft.h"
#include <ncursesw/curses.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>

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

enum entity_type
{
	PLAYER,
	BASIC_ENEMY,
	PLAYER_BULLET,
	ENEMY_BULLET,
	COLLIDABLE,
};

struct window
{
	WINDOW	*win;
	int		height;
	int		width;
	int		pos_y;
	int		pos_x;
};

struct coordinate {
	int x;
	int y;

	bool operator==(const coordinate& other) {
		return x == other.x && y == other.y;
	}
};

struct entity
{
	enum entity_type	type;
	bool	status;
	int		hp;
	int		speed;
	int		damage;
	long		invis_frames;
	long		shoot_cooldown;
	long		move_cooldown;
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
	//entity	bullets[MAX_BULLETS];
	/* window	game_win;
	window	status_win;
	entity	player;*/
	std::vector<entity>	enemies;
	std::vector<entity>	bullets;
	std::vector<entity>	collidables;
};
