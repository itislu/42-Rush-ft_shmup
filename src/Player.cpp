#include "Coordinate.hpp"
#include "game.hpp"
#include "time.hpp"
#include <ncurses.h>

Player::Player(int id_, Coordinate position)
    : Entity(),
      appearance(appearances.at(id_)),
      control_set{controls_sets.at(id_)}
{
	id = id_;
	current_pos = position;
	status = true;
	hp = 3;
}

bool Player::update(int input, Game* game)
{
	if (!status) {
		return false;
	}
	if (shared_players_hp(game) <= 0) {
		status = false;
	}

	bool got_input = true;
	if (input == control_set[0] && current_pos.y != 0) {
		current_pos.y--;
	}
	else if (input == control_set[1] && current_pos.x != 0) {
		current_pos.x--;
	}
	else if (input == control_set[2] && current_pos.y != map_height - 1) {
		current_pos.y++;
	}
	else if (input == control_set[3] && current_pos.x != map_width - 1) {
		current_pos.x++;
	}
	else if (input == control_set[4]) {
		auto_fire_toggle = false;
		shoot(game);
	}
	else if (input == control_set[5]) {
		auto_fire_toggle = !auto_fire_toggle;
	}
	else {
		got_input = false;
	}

	if (auto_fire_toggle) {
		shoot(game);
	}
	return got_input;
}

void Player::shoot(Game* game)
{
	if (!status) {
		return;
	}
	if (get_current_time() - shoot_cooldown > 200) {
		shoot_cooldown = get_current_time();

		Entity bullet = {};
		bullet.type = PLAYER_BULLET;
		bullet.status = true;
		bullet.damage = 1;
		bullet.speed = 1000;
		bullet.current_pos = current_pos;
		game->bullets.push_back(bullet);
	}
}

bool Player::on_collision(Entity* entity, Game* game)
{
	if (!status
	    || !((current_pos == entity->current_pos)
	         || (current_pos == entity->previous_pos
	             && previous_pos == entity->current_pos))) {
		return false;
	}
	if (get_current_time() - invis_frames > 1200 || entity->type == BASIC_ENEMY
	    || entity->type == ENEMY_1 || entity->type == ENEMY_2
	    || entity->type == BOSS) {
		invis_frames = get_current_time();
		hp--;
		if (entity->type != BOSS) {
			entity->status = false;
		}
	}
	else if (entity->type != BOSS) {
		entity->status = false;
	}
	if (shared_players_hp(game) <= 0) {
		status = false;
	}
	return true;
}

void Player::print(WINDOW* game_win)
{
	if (status) {
		if (get_current_time() - invis_frames >= 1200
		    || (((get_current_time() - invis_frames) / 100) % 2 != 0)) {
			mvwaddwstr(game_win,
			           current_pos.y + 1,
			           (current_pos.x * 2) + 2,
			           appearance);
		}
	}
	else {
		mvwaddwstr(game_win, current_pos.y + 1, (current_pos.x * 2) + 2, L"💥");
	}
}
