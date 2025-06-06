#pragma once

#include <ncurses.h>
#include <vector>

#define MAX_MAP_HEIGHT 20
#define MAX_MAP_WIDTH 20

#define MAX_ENEMIES 100
#define MAX_BULLETS 100

enum entity_type
{
	PLAYER,
	BASIC_ENEMY,
	BULLET,
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
};

struct entity
{
	int		type;
	bool	status;
	int		hp;
	int		speed;
	int		damage;
	int		shoot_cooldown;
	int		move_cooldown;
	std::vector<coordinate>	pattern;
	int		pattern_idx;
	coordinate	pos;
};

// struct player : public entity 
// {

// };

// struct enemy : public entity
// {

// };

struct game
{
	window	game_win;
	window	status_win;
	entity	player;
	std::vector<entity>	enemies;
	std::vector<entity>	bullets;
	std::vector<entity>	collidables;
};
