#pragma once

#include "Coordinate.hpp"
#include "GameObject.hpp"
#include "NcursesManager.hpp"
#include "utils/Pattern.hpp"

class Collidable : public GameObject {
public:
	explicit Collidable(Coordinate position)
	    : GameObject(GameObject::Type::COLLIDABLE,
	                 position,
	                 Pattern<Coordinate>({{-1, 0}}),
	                 500,
	                 -1,
	                 0)
	{}

	void render(NcursesManager& ncurses_manager) override;

	// does nothing itself, players and enemies move themselves back
	void on_collision(const GameObject& /*other*/) override {}

private:
	// movement pattern/strategy
	// shooting pattern/strategy
};
