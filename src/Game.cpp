#include "Game.hpp"
#include <chrono>

// Rough outline in Game::run()

// Initialization (done in Game constructor or a separate init method)
// _window_manager.initialize();
// levelManager_.load_level(1);
// GameObjectManager creates and returns a pointer
// player_ = _game_object_manager.add_player(...);

Game::run()
{
    auto last_time = std::chrono::high_resolution_clock::now();

	while (_current_game_state != GameState::EXITING) {
		auto current_time = std::chrono::high_resolution_clock::now();
		const float delta_time =
		    std::chrono::duration<float>(current_time - last_time).count();
		last_time = current_time;

		// 1. Process Input
		_input_handler.poll_input();
		if (_input_handler.is_key_pressed(KEY_ESCAPE)) {
			// quit
		}
		// Player input processing happens in Player::update, which queries
		_player->update_movement(_input_handler);

		// 2. Update Game Logic
		switch (_current_game_state) {
		case GameState::PLAYING:
			// _background_manager.update(delta_time);

			// Update all game_objects (player, enemies, bullets, collidables)
			_game_object_manager.update_all(delta_time);

			// Level progression and enemy spawning
			_level_manager.spawn(delta_time, _game_object_manager);

			// Update score, time, check lives
			if (_player && _player->get_lives() <= 0) {
				_current_game_state = GameState::GAME_OVER;
			}
			break;

		case GameState::GAME_OVER:
			// Continue updating game_objects for scrolling effect
			_game_object_manager.update_all(delta_time);
			// if (inputHandler_.is_key_pressed('r')) { /* restart logic */ }
			break;

		case GameState::MENU:
			// Handle menu logic, input for starting game, options, etc.
			break;

        case GameState::PAUSED:
            break;
		}

		// 2.5 Cleanup
		// Remove game_objects marked as inactive (destroyed bullets, dead
		// enemies)
		_game_object_manager.collect_inactive_objects();

		// 3. Render
		_window_manager.clear();

		_game_object_manager.render_all(_window_manager);

		_window_manager.refresh();

		// 4. Frame Rate Control
		auto frame_end_time = std::chrono::high_resolution_clock::now();
		float frame_duration =
		    std::chrono::duration<float>(frame_end_time - current_time).count();
		const float target_frame_time = 1.0f / 60.0f;
		if (frame_duration < target_frame_time) {
			std::this_thread::sleep_for(std::chrono::duration<float>(
			    target_frame_time - frame_duration));
		}
	}
}
