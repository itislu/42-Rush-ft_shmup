#pragma once

#include <vector>

class InputHandler {
public:
	void poll_input();

	// Check if a specific key is pressed
	bool is_key_pressed(int key);

	std::vector<int> get_pressed_keys();
};
