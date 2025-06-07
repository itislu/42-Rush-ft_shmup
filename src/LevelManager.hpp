#pragma once

#include "GameObjectManager.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

class LevelManager {
public:
	// Uses game_object_manager to add new enemies
	// Makes sure to not spawn an enemy on another game_object
	void spawn(float delta_time, GameObjectManager& game_object_manager)
	try {
		const Wave& cur_wave = _level_data->waves.at(_cur_wave_index);

		if (_cur_spawn_event_index == cur_wave.spawn_events.size()) {
			++_cur_wave_index;
			_cur_spawn_event_index = 0;
			_time_in_wave = 0;
		}
		_time_in_wave += delta_time;

		while (cur_wave.spawn_events.at(_cur_spawn_event_index).time_offset
		       <= _time_in_wave) {
			const SpawnEvent& spawn_event =
			    cur_wave.spawn_events[_cur_spawn_event_index];

            // TODO Make sure it is a non-occupied position

			// TODO Create a spawn out of the spawn_event

			// TODO Add the spawn to game_object_manager

			++_cur_spawn_event_index;
		}
	}
	catch (const std::out_of_range&) {
		return;
	}

private:
	struct Level;
	struct Wave;
	struct SpawnEvent;

	const Level* _level_data = &level1();
	std::size_t _cur_wave_index = 0;
	std::size_t _cur_spawn_event_index = 0;
	float _time_in_wave = 0.0F;

	struct Level {
		std::vector<Wave> waves;
	};

	struct Wave {
		std::vector<SpawnEvent> spawn_events;
	};

	struct SpawnEvent {
		float time_offset;
		float x_percentage;
		float y_percentage;
		// enemy type
	};

	static const Level& level1()
	{
		// clang-format off
        static const Level level1 {
            { // Waves
                { // Wave 1
                    { // SpawnEvents
                        {.time_offset=0, .x_percentage=101, .y_percentage=10},
                        {.time_offset=0, .x_percentage=101, .y_percentage=30},
                        {.time_offset=0, .x_percentage=101, .y_percentage=50},
                        {.time_offset=0, .x_percentage=101, .y_percentage=70},
                        {.time_offset=0, .x_percentage=101, .y_percentage=90},
                    }
                },
                { // Wave 2
                    {
                        {.time_offset=0, .x_percentage=101, .y_percentage=10},
                        {.time_offset=0, .x_percentage=101, .y_percentage=30},
                        {.time_offset=0, .x_percentage=101, .y_percentage=50},
                        {.time_offset=0, .x_percentage=101, .y_percentage=70},
                        {.time_offset=0, .x_percentage=101, .y_percentage=90},
                    }
                }
            }
        };
		// clang-format on
		return level1;
	}
};
