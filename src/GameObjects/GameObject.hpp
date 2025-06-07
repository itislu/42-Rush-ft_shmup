// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

#pragma once

#include "Coordinate.hpp"
#include "NcursesManager.hpp"
#include "utils/Pattern.hpp"
#include <cstdint>

class GameObjectManager;

class GameObject {
public:
	enum class Type : std::uint8_t {
		PLAYER,
		ENEMY,
		BULLET,
		COLLIDABLE,
	};

	GameObject(Type type,
	           Coordinate position,
	           const Pattern<Coordinate>& move_pattern,
	           float move_interval,
	           float action_interval,
	           int score)
	    : _type(type),
	      _position(position),
	      _prev_position(position),
	      _move_pattern(move_pattern),
	      _move_interval(move_interval),
	      _action_interval(action_interval),
	      _score(score)
	{}
	GameObject(const GameObject&) = default;
	GameObject& operator=(const GameObject&) = default;
	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;
	virtual ~GameObject() = default;

	// move if enough time has passed
	virtual void move(float delta_time)
	{
		_move_cooldown_timer -= delta_time;
		if (_move_cooldown_timer < 0) {
			_prev_position = _position;
			_position += _move_pattern.next();
			_move_cooldown_timer += _move_interval;
		}
	}
	// shooting, f.e.
	virtual void action(float /*delta_time*/,
	                    GameObjectManager& /*game_object_manager*/)
	{}
	// how to draw itself
	virtual void render(NcursesManager& ncurses_manager) = 0;
	// what to do when it collides
	virtual void on_collision(const GameObject& other) = 0;

	Type get_type() const { return _type; };
	int get_score() const { return _score; };
	bool is_active() const { return _is_active; };

protected:
	Type _type;
	Coordinate _position;
	Coordinate _prev_position;
	Pattern<Coordinate> _move_pattern;
	float _move_interval;
	float _move_cooldown_timer;
	float _action_interval;
	float _action_cooldown_timer;
	// int _health;
	// int _damage;
	int _score;
	bool _is_active = true;
	// dimensions
};

// NOLINTEND(misc-non-private-member-variables-in-classes)
