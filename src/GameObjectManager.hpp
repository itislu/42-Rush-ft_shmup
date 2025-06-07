#pragma once

#include "GameObjects/GameObject.hpp"
#include "NcursesManager.hpp"
#include <memory>
#include <vector>

class GameObjectManager {
public:
	void add_game_object(std::unique_ptr<GameObject> game_object);

	// iterates and calls update() on each game_object, then checks for
	// collisions
	// collision resolution calls on_collision() on both objects
	void update_all(float delta_time);

	// iterates and calls render() on each game_object
	void render_all(NcursesManager& ncurses_manager);

	// removes objects where is_active is false and return collected score
	long collect_inactive_objects();

	// or delegate to a CollisionSystem
	std::vector<GameObject*> get_colliding_pairs();

	std::vector<GameObject*> get_objects_by_type(GameObject::Type type);

private:
	std::vector<std::unique_ptr<GameObject>> _game_objects;
};
