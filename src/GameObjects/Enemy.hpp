#pragma once

#include "Coordinate.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "GameObjects/Bullet.hpp"
#include "NcursesManager.hpp"
#include "utils/Pattern.hpp"
#include <memory>

// Inherit from Enemy to implement specific enemy type
class Enemy : public GameObject {
public:
	void action(float delta_time,
	            GameObjectManager& game_object_manager) override
	{
		_action_cooldown_timer -= delta_time;
		if (_action_cooldown_timer < 0) {
			_action_cooldown_timer += _action_interval;
			game_object_manager.add_game_object(
			    std::make_unique<Bullet>(Bullet({_position.x - 1, _position.y},
			                                    GameObject::Type::ENEMY,
			                                    *_bullet_pattern)));
		}
	}

	void render(NcursesManager& ncurses_manager) override
	{
		ncurses_manager.draw_game_character(_position.y, _position.x, '<');
	}

	void on_collision(const GameObject& other) override
	{
		if (!other.is_active()) {
			return;
		}
		switch (other.get_type()) {
		case GameObject::Type::BULLET:
			if (dynamic_cast<const Bullet&>(other).get_owner_type() == GameObject::Type::PLAYER) {
				_is_active = false;
			}
			break;
		case GameObject::Type::COLLIDABLE:
			// TODO
			_is_active = false;
			break;
		case GameObject::Type::ENEMY:
		case GameObject::Type::PLAYER:
			break;
		}
	}

private:
	static const Pattern<Coordinate>& _get_bullet_pattern()
	{
		static const Pattern<Coordinate> pattern({{1, 0}});
		return pattern;
	}

	inline static const Pattern<Coordinate>* const _bullet_pattern =
	    &_get_bullet_pattern();
	// movement pattern/strategy
	// shooting pattern/strategy
};
