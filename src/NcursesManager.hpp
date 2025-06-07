#pragma once

#include <ncurses.h>
#include <string>

class NcursesManager {
public:
	NcursesManager(int game_height, int game_width) :
        _game_height(game_height), _game_width(game_width)
    {
        // ncurses init
		// _game_window = 
    }
    ~NcursesManager() {
		delwin(_game_window);
		delwin(_status_window);
	}

	void clear();
	void draw_game_character(int y, int x, char ch, int color_pair = 0)
	{
		(void)color_pair;
		mvwprintw(_game_window, y, x, "%c", ch);
	}
	// void draw_string(WINDOW* win,
	//                  int y,
	//                  int x,
	//                  const std::string& str,
	//                  int color_pair = 0);
	void refresh();
	int get_game_width() const;
	int get_game_height() const;

private:
	WINDOW* _game_window;
	WINDOW* _status_window;
	int _game_height;
	int _game_width;
	int _status_height;
	int _status_width;
};
