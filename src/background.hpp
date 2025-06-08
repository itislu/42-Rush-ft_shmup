#pragma once

#include "coordinate.hpp"
#include <cstddef>
#include <ncurses.h>
#include <vector>

struct background_entity 
{
	const wchar_t* ch;
	coordinate current_pos;
	std::vector<coordinate> pattern;
	size_t pattern_idx;
};

struct background 
{
	background();
	void update();
	void spawn(int x);
	void print(WINDOW* game_win);
    void prune();

	std::vector<background_entity> entities;
	std::vector<const wchar_t*> charset = {L"𖥔", L"✦", L"˖", L".", L" ݁ "};
	long spawn_cooldown;
	long move_cooldown;
};
