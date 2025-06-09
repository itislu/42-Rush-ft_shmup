#pragma once

#include "Coordinate.hpp"
#include <cstddef>
#include <ncurses.h>
#include <vector>

struct BackgroundEntity 
{
	const wchar_t* ch;
	Coordinate current_pos;
	std::vector<Coordinate> pattern;
	size_t pattern_idx;
};

struct Background 
{
	Background();
	void update();
	void spawn(int x);
	void print(WINDOW* game_win);
    void prune();

	std::vector<BackgroundEntity> entities;
	std::vector<const wchar_t*> charset = {L"𖥔", L"✦", L"˖", L".", L" ݁ "};
	long spawn_cooldown;
	long move_cooldown;
};
