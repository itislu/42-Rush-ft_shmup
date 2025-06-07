#pragma once

#include "Coordinate.hpp"
#include "GameObject.hpp"
#include "NcursesManager.hpp"
#include "utils/Pattern.hpp"

class Bullet : public GameObject {
public:
	Bullet(Coordinate position,
	       Type owner_type,
	       const Pattern<Coordinate>& move_pattern)
	    : GameObject(GameObject::Type::BULLET,
	                 position,
	                 move_pattern,
	                 1000,
	                 -1,
	                 10),
	      _owner_type(owner_type)
	{}

	void render(NcursesManager& ncurses_manager) override
	{
		char c = '-';
		if (_owner_type == GameObject::Type::PLAYER) {
			c = '-';
		}
		ncurses_manager.draw_game_character(_position.y, _position.x, c);
	}

	void on_collision(const GameObject& other) override
	{
		if (!other.is_active()) {
			return;
		}
		switch (other.get_type()) {
		case GameObject::Type::BULLET:
			if (_owner_type != dynamic_cast<const Bullet&>(other)._owner_type) {
				_is_active = false;
			}
			break;
		case GameObject::Type::COLLIDABLE:
			_is_active = false;
			break;
		case GameObject::Type::ENEMY:
			if (_owner_type != GameObject::Type::ENEMY) {
				_is_active = false;
			}
			break;
		case GameObject::Type::PLAYER:
			if (_owner_type != GameObject::Type::PLAYER) {
				_is_active = false;
			}
			break;
		}
	}

	GameObject::Type get_owner_type() const { return _owner_type; }

private:
	// int damage; // if player has health
	GameObject::Type _owner_type; // to identify if it's player or enemy bullet

	// movement pattern/strategy
	// shooting pattern/strategy
};
