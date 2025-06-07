#pragma once

#include "GameObjectManager.hpp"
#include "GameObjects/Player.hpp"
#include "InputHandler.hpp"
#include "LevelManager.hpp"
#include "NcursesManager.hpp"
#include <cstdint>

class Game {
	enum class GameState : std::uint8_t {
		MENU,
		PLAYING,
		GAME_OVER,
		PAUSED
	};

    static const int game_height = 42;
    static const int game_width = 42;

	// contains the main game loop and does frame rate control
	void run();

private:
	// Use their respective managers
	void _process_input();
	void _update(float delta_time);
	void _render();
	void _handle_game_over();
	void _add_score(long points);

	NcursesManager _window_manager{game_height, game_width};
	InputHandler _input_handler;
	GameObjectManager _game_object_manager;
	LevelManager _level_manager;
	// BackgroundManager _background_manager;
	Player* _player{}; // a raw pointer, as GameObjectManager owns the Player
	GameState _current_game_state{}; // MENU, PLAYING, GAME_OVER, PAUSED
	long _score{};
	float _game_time{};
	float _delta_time{};
};
