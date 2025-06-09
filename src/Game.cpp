#include "game.hpp"
#include <ncurses.h>

Game::Game()
{
	getmaxyx(stdscr, term_height, term_width);

	game_width = term_width;
	status_width = term_width;

	status_height = STATUS_WINDOW_HEIGHT;
	game_height = term_height - status_height;
}
