#pragma once

#include "Coordinate.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "GameObjects/Bullet.hpp"
#include "InputHandler.hpp"
#include "NcursesManager.hpp"
#include "utils/Pattern.hpp"
#include <memory>
#include <vector>

class Player : public GameObject {
public:
	// overwrites _move_pattern
	void update_movement(InputHandler& input_handler); // do input_handler first

	void action(float delta_time,
	            GameObjectManager& game_object_manager) override
	{
		_action_cooldown_timer -= delta_time;
		if (_action_cooldown_timer < 0) {
			_action_cooldown_timer += _action_interval;
			game_object_manager.add_game_object(
			    std::make_unique<Bullet>(Bullet({_position.x + 1, _position.y},
			                                    GameObject::Type::PLAYER,
			                                    *_bullet_pattern)));
		}
	}

	void render(NcursesManager& ncurses_manager) override;

	void on_collision(const GameObject& other) override;

private:
	static const Pattern<Coordinate>& _get_bullet_pattern()
	{
		static const Pattern<Coordinate> pattern({{1, 0}});
		return pattern;
	}

	inline static const Pattern<Coordinate>* const _bullet_pattern =
	    &_get_bullet_pattern();
	int _lives;
	// int _damage;
};
