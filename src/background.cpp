#include "background.hpp"
#include "game.hpp"
#include "time.hpp"
#include <algorithm>
#include <cstdlib>
#include <ncurses.h>

background::background()
    : spawn_cooldown(0),
      move_cooldown(0)
{
	for (int x = 0; x < map_width; ++x) {
		spawn(x);
	}
}

void background::update()
{
	// Spawn
	if (get_current_time() - spawn_cooldown > 100) {
		spawn_cooldown = get_current_time();
		spawn(map_width);
	}

	// Move
	if (get_current_time() - move_cooldown > 80) {
		move_cooldown = get_current_time();

		for (auto& bg : entities) {
			bg.current_pos += bg.pattern[bg.pattern_idx];
			bg.pattern_idx = (bg.pattern_idx + 1) % bg.pattern.size();
		}
	}
}

void background::spawn(int x)
{
	background_entity bg = {};
	bg.pattern = {{-1, 0}};
	bg.current_pos.x = x;
	bg.current_pos.y = rand() % map_height;
	bg.ch = charset[rand() % charset.size()];

	entities.push_back(bg);
}

void background::print(WINDOW* game_win)
{
	for (auto& bg : entities) {
		mvwaddwstr(
		    game_win, bg.current_pos.y + 1, bg.current_pos.x * 2 + 2, bg.ch);
	}
}

void background::prune()
{
	entities.erase(std::remove_if(entities.begin(),
	                              entities.end(),
	                              [](background_entity& bg) {
		                              return bg.current_pos.x < 0;
	                              }),
	               entities.end());
}
