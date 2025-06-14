#include "game.hpp"
#include "libftpp/format.hpp"
#include "time.hpp"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctype.h>
#include <exception>
#include <iostream>
#include <locale.h>
#include <optional>
#include <sys/types.h>

int map_width;
int map_height;

short rgb_to_ncurses(int rgb)
{
	return (rgb * 1000 / 255);
}

bool	init_ncurses()
{
	if (!initscr())
		return (false);
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	//cbreak();
	ESCDELAY = 0;
	setlocale(LC_ALL, "");
	start_color();
	use_default_colors();
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_GREEN, -1);
	init_pair(3, COLOR_YELLOW, -1);
	init_pair(4, COLOR_BLUE, -1);
	init_pair(5, COLOR_MAGENTA, -1);
	init_pair(6, COLOR_CYAN, -1);
	init_color(COLOR_ORANGE, rgb_to_ncurses(255),rgb_to_ncurses(145),rgb_to_ncurses(0));
	init_pair(COLOR_ORANGE, COLOR_ORANGE, -1);
	return (true);
}

WINDOW *create_win(int size_y, int size_x , int pos_y, int pox_x)
{
	WINDOW *win = newwin(size_y, size_x, pos_y, pox_x);
	keypad(win, TRUE);
	return (win);
}

void	init_win(Game *game)
{
	game->game_win = create_win(game->game_height, game->game_width, GAME_WINDOW_Y, GAME_WINDOW_X);
	game->status_win = create_win(game->status_height, game->status_width, STATUS_WINDOW_Y, STATUS_WINDOW_X);
	wrefresh(game->game_win);
	wrefresh(game->status_win);
	clear();
}

void	delete_win(Game *game)
{
	if (game->game_win != NULL)
	{
		delwin(game->game_win);
		game->game_win = NULL;
		clear();
	}
	if (game->status_win != NULL)
	{
		delwin(game->status_win);
		game->status_win = NULL;
		clear();
	}
}

int shared_players_hp(Game *game)
{
	int shared_hp = 0;
	for (auto& player : game->players) {
		shared_hp += player.hp;
	}
	return shared_hp;
}

void	print_status(Game *game)
{
	for (int j = 0; j < game->status_height; j++)
	{
		for (int k = 0; k < game->status_width; k++)
		{
			mvwprintw(game->status_win, j, k, " ");
		}
	}
	box(game->status_win, 0, 0);
	const int shared_hp = shared_players_hp(game);
	for (int i = 0; i < shared_hp; i++)
	{
		mvwaddwstr(game->status_win, 1, game->status_width / 2 - 9 + i * 3, L"❤️");
	}
	mvwaddwstr(game->status_win, 1, 2, L"⏱️");
	mvwprintw(game->status_win, 1, 4, " Time: %ld", 
		(shared_hp > 0 ? get_current_time_in_seconds() : game->gameover_time) - game->start_time);
	mvwaddwstr(game->status_win, 1, game->status_width - 16, L"🏆");
	mvwprintw(game->status_win, 1, game->status_width - 14, " Score: %ld", game->score);
	wrefresh(game->status_win);
}

bool	is_bullet(Game *game, int y, int x, int type)
{
	for (size_t i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i].status == 1 && game->bullets[i].type == type
			&& game->bullets[i].current_pos.y == y
			&& game->bullets[i].current_pos.x == x)
			return (true);
	}
	return (false);
}

bool	is_enemy(Game *game, int y, int x, int type)
{
	for (size_t i = 0; i < game->enemies.size(); i++)
	{
		if (game->enemies[i].status == 1 && game->enemies[i].type == type
			&& game->enemies[i].current_pos.y == y
			&& game->enemies[i].current_pos.x == x)
			return (true);
	}
	return (false);
}

void print_gameover(Game *game)
{
	const size_t game_over_height = sizeof(game_over) / sizeof(game_over[0]);
	const size_t game_over_width = 40;
	const size_t start_y = (game->game_height / 2) - (game_over_height / 2);
	const size_t start_x = (game->game_width / 2) - (game_over_width / 2);

	for (int y = 0; y < 13; y++){
		mvwaddwstr(game->game_win, start_y + y, start_x, game_over[y]);
	}
}

void	print_game(Game *game)
{
	// Clear window
	for (int y = 0; y < game->game_height; y++)
	{
		for(int x = 0; x < game->game_width; x++)
		{
			mvwaddwstr(game->game_win, y, x, L" ");
		}
	}

	// Background
	game->background.print(game->game_win);

	// Entities
	for (auto& bullet : game->bullets) {
		if (!bullet.status) {
			continue;
		}
		if (bullet.type == PLAYER_BULLET) {
			wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_GREEN), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"——");
			wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_GREEN), 0);
		}
		else if (bullet.type == ENEMY_BULLET) {
			if (bullet.source == BOSS)
				wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_RED), 0);
			else
				wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_MAGENTA), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"——");
			if (bullet.source == BOSS)
				wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_RED), 0);
			else
				wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_MAGENTA), 0);
		}
		else if (bullet.type == ENEMY_1_BULLET) {
			wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_CYAN), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"——");
			wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_CYAN), 0);
		}
		else if (bullet.type == HOMING_BULLET) {
			wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_ORANGE), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"● ");
			wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_ORANGE), 0);
		}
		else if (bullet.type == TRUE_HOMING_BULLET)
		{
			wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_RED), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"● ");
			wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_RED), 0);
		}
	}
	for (auto& player : game->players) {
		player.print(game->game_win);
	}
	for (auto& enemy : game->enemies) {
		if (!enemy.status) {
			continue;
		}
		if (enemy.type == BASIC_ENEMY) {
			mvwaddwstr(game->game_win, enemy.current_pos.y + 1, enemy.current_pos.x * 2 + 2, L"👾");
		}
		else if (enemy.type == ENEMY_2) {
			mvwaddwstr(game->game_win, enemy.current_pos.y + 1, enemy.current_pos.x * 2 + 2, L"👽");
		}
		else if (enemy.type == ENEMY_1) {
			mvwaddwstr(game->game_win, enemy.current_pos.y + 1, enemy.current_pos.x * 2 + 2, L"🗿");
		}
		else if (enemy.type == BOSS) {
			if (enemy.id == 5)
				mvwaddwstr(game->game_win, enemy.current_pos.y + 1, enemy.current_pos.x * 2 + 2, L"👀");
			else
				mvwaddwstr(game->game_win, enemy.current_pos.y + 1, enemy.current_pos.x * 2 + 2, L"🟥");
		}
	}
	for (auto& collidable : game->collidables) {
		if (!collidable.status) {
			continue;
		}
	}
	if (shared_players_hp(game) <= 0) {
		print_gameover(game);
	}

	box(game->game_win, 0, 0);
	wrefresh(game->game_win);
}

void	print_stuff(Game *game)
{
	print_game(game);
	print_status(game);
}

void	spawn_enemy_bullet(Game *game, Entity *enemy, int bullet_type, int source)
{
	enemy->shoot_cooldown = get_current_time();
	if (enemy->type != BOSS && rand() % 2 == 0)
		return ;
	Entity bullet = {};
	bullet.type = bullet_type;
	bullet.source = source;
	bullet.status = 1;
	bullet.damage = 1;
	bullet.speed = 1000;
	bullet.current_pos.y = enemy->current_pos.y;
	bullet.current_pos.x = enemy->current_pos.x;
	bullet.pattern = {LEFT};
	game->bullets.push_back(bullet);
}

void	move_p_bullet(Entity *bullet)
{
	bullet->move_cooldown = get_current_time();
	bullet->previous_pos = bullet->current_pos;
	bullet->current_pos.x++;
}

std::optional<Player *> find_nearest_player_in_x(Game *game, Entity *entity)
{
	int min_distance_y = INT_MAX;
	std::optional<Player *> nearest_player = std::nullopt;

	for (auto& player : game->players) {
		if (player.current_pos.x != entity->current_pos.x || player.status == 0) {
			continue;
		}
		const int distance_y = std::abs(player.current_pos.y - entity->current_pos.y);
		if (!nearest_player || distance_y < min_distance_y) {
			min_distance_y = distance_y;
			nearest_player = &player;
		}
	}
	return nearest_player;
}

std::optional<Player *> find_nearest_player_in_y(Game *game, Entity *entity)
{
	int min_distance_x = INT_MAX;
	std::optional<Player *> nearest_player = std::nullopt;

	for (auto& player : game->players) {
		if (player.current_pos.y != entity->current_pos.y || player.status == 0) {
			continue;
		}
		const int distance_x = std::abs(player.current_pos.x - entity->current_pos.x);
		if (!nearest_player || distance_x < min_distance_x) {
			min_distance_x = distance_x;
			nearest_player = &player;
		}
	}
	return nearest_player;
}

void	move_true_homing_bullet(Game *game, Entity *bullet)
{
	auto nearest_player_y = find_nearest_player_in_y(game, bullet);
	auto nearest_player_x = find_nearest_player_in_x(game, bullet);
	if (nearest_player_y && nearest_player_x)
	{
		const int distance_y = std::abs((*nearest_player_y)->current_pos.x - bullet->current_pos.x);
		const int distance_x = std::abs((*nearest_player_x)->current_pos.y - bullet->current_pos.y);
		if (distance_y < distance_x)
		{
			if ((*nearest_player_y)->current_pos.x < bullet->current_pos.x)
				bullet->pattern = {LEFT};
			else
				bullet->pattern = {RIGHT};
		}
		else
		{
			if ((*nearest_player_x)->current_pos.y < bullet->current_pos.y)
				bullet->pattern = {UP};
			else
				bullet->pattern = {DOWN};
		}
	}
	else if (nearest_player_y)
	{
		if ((*nearest_player_y)->current_pos.x < bullet->current_pos.x)
			bullet->pattern = {LEFT};
		else
			bullet->pattern = {RIGHT};
	}
	else if (nearest_player_x)
	{
		if ((*nearest_player_x)->current_pos.y < bullet->current_pos.y)
			bullet->pattern = {UP};
		else
			bullet->pattern = {DOWN};
	}
	bullet->current_pos.y += bullet->pattern[0].y;
	bullet->current_pos.x += bullet->pattern[0].x;
}

void	move_enemy_bullets(Game *game, Entity *bullet)
{
	bullet->move_cooldown = get_current_time();
	bullet->previous_pos = bullet->current_pos;
	if (bullet->type == TRUE_HOMING_BULLET)
	{
		move_true_homing_bullet(game, bullet);
		return ;
	}
	if (bullet->type == HOMING_BULLET && bullet->direction == 0)
	{
		auto nearest_player = find_nearest_player_in_x(game, bullet);
		if (nearest_player && (*nearest_player)->status 
			&& (*nearest_player)->current_pos.y != bullet->current_pos.y) 
		{
			if ((*nearest_player)->current_pos.y < bullet->current_pos.y)
				bullet->direction = -1;
			else
				bullet->direction = 1;
		}
	}
	if (bullet->type == HOMING_BULLET && bullet->direction != 0)
		bullet->current_pos.y += bullet->direction;
	else
		bullet->current_pos.x--;
}

void	move_enemy(Entity *enemy)
{
	enemy->move_cooldown = get_current_time();
	if (enemy->pattern_idx >= enemy->pattern.size())
		enemy->pattern_idx = 0;
	enemy->previous_pos = enemy->current_pos;
	enemy->current_pos.y += enemy->pattern[enemy->pattern_idx].y;
	enemy->current_pos.x += enemy->pattern[enemy->pattern_idx].x;
	enemy->pattern_idx++;
}

void	update_entities(Game *game)
{
	for (size_t i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i].status == 1 && game->bullets[i].type == PLAYER_BULLET
			&& get_current_time() - game->bullets[i].move_cooldown > 20)
			move_p_bullet(&game->bullets[i]);
		else if (game->bullets[i].status == 1 && game->bullets[i].source != BOSS
			&& ((game->bullets[i].type == ENEMY_BULLET && get_current_time() - game->bullets[i].move_cooldown > 80)
				|| (game->bullets[i].type == ENEMY_1_BULLET && get_current_time() - game->bullets[i].move_cooldown > 100)
				|| (game->bullets[i].type == HOMING_BULLET && get_current_time() - game->bullets[i].move_cooldown > 180)))
			move_enemy_bullets(game, &game->bullets[i]);
		else if (game->bullets[i].status == 1 && game->bullets[i].source == BOSS
			&& ((game->bullets[i].type == ENEMY_BULLET && get_current_time() - game->bullets[i].move_cooldown > 50)
			|| (game->bullets[i].type == TRUE_HOMING_BULLET && get_current_time() - game->bullets[i].move_cooldown > 170)))
			move_enemy_bullets(game, &game->bullets[i]);
	}
	for (size_t i = 0; i < game->enemies.size(); i++)
	{
		if (game->enemies[i].status == 1 && game->enemies[i].type == BASIC_ENEMY
			&& get_current_time() - game->enemies[i].move_cooldown > 350)
				move_enemy(&game->enemies[i]);
		if (game->enemies[i].status == 1 && game->enemies[i].type == BASIC_ENEMY
			&& get_current_time() - game->enemies[i].shoot_cooldown > 1200)
				spawn_enemy_bullet(game, &game->enemies[i], ENEMY_BULLET, BASIC_ENEMY);
		if (game->enemies[i].status == 1 && game->enemies[i].type == ENEMY_1
			&& get_current_time() - game->enemies[i].move_cooldown > 300)
				move_enemy(&game->enemies[i]);
		if (game->enemies[i].status == 1 && game->enemies[i].type == ENEMY_1
			&& get_current_time() - game->enemies[i].shoot_cooldown > 1500)
				spawn_enemy_bullet(game, &game->enemies[i], ENEMY_1_BULLET, ENEMY_1);
		if (game->enemies[i].status == 1 && game->enemies[i].type == ENEMY_2
			&& get_current_time() - game->enemies[i].move_cooldown > 350)
				move_enemy(&game->enemies[i]);
		if (game->enemies[i].status == 1 && game->enemies[i].type == ENEMY_2
			&& get_current_time() - game->enemies[i].shoot_cooldown > 2500)
				spawn_enemy_bullet(game, &game->enemies[i], HOMING_BULLET, ENEMY_2);
		if (game->enemies[i].status == 1 && game->enemies[i].type == BOSS
			&& get_current_time() - game->enemies[i].move_cooldown > 200)
				move_enemy(&game->enemies[i]);
		if (game->enemies[i].status == 1 && (game->enemies[i].type == BOSS && (game->enemies[i].id == 1 || game->enemies[i].id == 3))
			&& get_current_time() - game->enemies[i].shoot_cooldown > 1000)
				spawn_enemy_bullet(game, &game->enemies[i], TRUE_HOMING_BULLET, BOSS);
		if (game->enemies[i].status == 1 && (game->enemies[i].type == BOSS && game->enemies[i].id == 2)
			&& get_current_time() - game->enemies[i].shoot_cooldown > 200)
				spawn_enemy_bullet(game, &game->enemies[i], ENEMY_BULLET, BOSS);
	}
}

void	spawn_basic_enemy(Game *game, int y, int x)
{
	Entity enemy = {};
	enemy.status = 1;
	enemy.type = BASIC_ENEMY;
	enemy.current_pos.y = y;
	enemy.current_pos.x = x;
	enemy.hp = 1;
	enemy.damage = 1;
	enemy.shoot_cooldown = get_current_time() - rand() % 2000;
	enemy.move_cooldown = get_current_time() - rand() % 2000;
	enemy.pattern = {LEFT, DOWN, LEFT, UP};
	game->enemies.push_back(enemy);
}

void	spawn_enemy_1(Game *game, int y, int x)
{
	Entity enemy = {};
	enemy.status = 1;
	enemy.type = ENEMY_1;
	enemy.current_pos.y = y;
	enemy.current_pos.x = x;
	enemy.hp = 1;
	enemy.damage = 1;
	enemy.shoot_cooldown = get_current_time() - rand() % 2000;
	enemy.move_cooldown = get_current_time() - rand() % 2000;
	enemy.pattern = {LEFT};
	game->enemies.push_back(enemy);
}

void	spawn_enemy_2(Game *game, int y, int x)
{
	Entity enemy = {};
	enemy.status = 1;
	enemy.type = ENEMY_2;
	enemy.current_pos.y = y;
	enemy.current_pos.x = x;
	enemy.hp = 1;
	enemy.damage = 1;
	enemy.shoot_cooldown = get_current_time() - rand() % 2000;
	enemy.move_cooldown = get_current_time() - rand() % 2000;
	enemy.pattern = {LEFT, UP, LEFT, DOWN, LEFT, DOWN, LEFT, UP};
	game->enemies.push_back(enemy);
}

void	spawn_boss(Game *game, int y, int x, int id)
{
	Entity enemy = {};
	enemy.status = 1;
	enemy.id = id;
	enemy.type = BOSS;
	enemy.current_pos.y = y;
	enemy.current_pos.x = x;
	enemy.hp = 1;
	game->boss_health = 9;
	game->boss_status = 1;
	enemy.damage = 2;
	enemy.shoot_cooldown = get_current_time();
	enemy.move_cooldown = get_current_time();
	for (int i = 0; i < (map_height / 2) - 3; i++){
		enemy.pattern.push_back(UP);
	}
	for (int i = 0; i < ((map_height / 2) - 3) * 2; i++){
		enemy.pattern.push_back(DOWN);
	}
	for (int i = 0; i < (map_height / 2) - 3; i++){
		enemy.pattern.push_back(UP);
	}
	//enemy.pattern = {UP, UP, UP, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, UP, UP, UP};
	game->enemies.push_back(enemy);
}

void	spawn_entities(Game *game)
{
	static int i = 0;
	if (!(get_current_time() - game->enemy_spawn_cooldown > 5000)
		|| shared_players_hp(game) <= 0)
		return ;
	game->enemy_spawn_cooldown = get_current_time();
	if (game->score >= 500 && get_current_time() - game->spawn_boss_cooldown > 25000 && game->boss_status == 0) //change values
	{
		//game->boss_health 
		spawn_boss(game,  map_height / 2 + 1, map_width - 6, 1);
		spawn_boss(game,  map_height / 2, map_width - 6, 2);
		spawn_boss(game,  map_height / 2 - 1, map_width - 6, 3);

		spawn_boss(game,  map_height / 2 + 1, map_width - 5, 4);
		spawn_boss(game,  map_height / 2, map_width - 5, 5);
		spawn_boss(game,  map_height / 2 - 1, map_width - 5, 6);

		spawn_boss(game,  map_height / 2 + 1, map_width - 4, 7);
		spawn_boss(game,  map_height / 2, map_width - 4, 8);
		spawn_boss(game,  map_height / 2 - 1, map_width - 4, 9);

	}
	else if (game->boss_health == 0)
	{
		for (int y = 0; y < map_height - 1; y++)
		{
			if (i == 0 && rand() % 3 == 0)
			{
				spawn_enemy_1(game, y, map_width - 1);
				y++;
			}
			else if (i == 1 && rand() % 3 == 0)
			{
				spawn_basic_enemy(game, y, map_width - 1);
				y++;
			}
			else if (i == 2 && rand() % 3 == 0)
			{
				spawn_enemy_2(game, y, map_width - 1);
				y++;
			}
		}
		i++;
		if (i == 3)
			i = 0;
	}
}

void	check_bullet_collision(Game *game, Entity *entity, int type)
{
	for (size_t i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i].status == 1 && game->bullets[i].type == type
			&& ((game->bullets[i].current_pos == entity->current_pos)
			|| (game->bullets[i].current_pos == entity->previous_pos 
				&& game->bullets[i].previous_pos == entity->current_pos)))
		{
			game->bullets[i].status = false;
			entity->status = false;
		}
	}
}

void kill_boss(Game *game)
{
	for (size_t i = 0; i < game->enemies.size(); i++)
	{
		if (game->enemies[i].type == BOSS && game->boss_health <= 0) {
					game->enemies[i].status = false;
				}
	}
}

void	check_enemy_collision(Game *game, Entity *entity, int type)
{
	for (size_t i = 0; i < game->enemies.size(); i++)
	{
		if (game->enemies[i].status == 1 && game->enemies[i].type == type
			&& ((game->enemies[i].current_pos == entity->current_pos)
			|| (game->enemies[i].current_pos == entity->previous_pos 
				&& game->enemies[i].previous_pos == entity->current_pos)))
		{
			if (type == BASIC_ENEMY)
				game->score += BASIC_ENEMY_POINTS;
			else if (type == ENEMY_2)
				game->score += ENEMY_2_POINTS;
			else if (type == ENEMY_1)
				game->score += ENEMY_1_POINTS;
			else if (type == BOSS) {
				game->boss_health--;
				if (game->boss_health <= 0) {
					for (auto& player : game->players) {
						if (player.status)
							player.hp += 1;
					}
					game->score += BOSS_POINTS;
					game->spawn_boss_cooldown = get_current_time();
					game->boss_status = 0;
					kill_boss(game);
				}
			}
			entity->status = false;
			if (type != BOSS)
				game->enemies[i].status = false;
			return ;
		}
	}
}

void	check_collisions(Game *game)
{
	for (size_t i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i].status == 1 && game->bullets[i].type == PLAYER_BULLET)
		{
			check_bullet_collision(game, &game->bullets[i], ENEMY_BULLET);
			check_bullet_collision(game, &game->bullets[i], ENEMY_1_BULLET);
			check_bullet_collision(game, &game->bullets[i], HOMING_BULLET);
			check_bullet_collision(game, &game->bullets[i], TRUE_HOMING_BULLET);
			check_enemy_collision(game, &game->bullets[i], BASIC_ENEMY);
			check_enemy_collision(game, &game->bullets[i], ENEMY_2);
			check_enemy_collision(game, &game->bullets[i], ENEMY_1);
			check_enemy_collision(game, &game->bullets[i], BOSS);
		}
		if (game->bullets[i].status == 1 && (game->bullets[i].type == ENEMY_BULLET || game->bullets[i].type == HOMING_BULLET || game->bullets[i].type == ENEMY_1_BULLET || game->bullets[i].type == TRUE_HOMING_BULLET))
		{
			for (auto& player : game->players) {
				player.on_collision(&game->bullets[i], game);
			}
		}
		
	}
	for (size_t i = 0; i < game->enemies.size(); i++) {
		if (game->enemies[i].status == 1
			&& (game->enemies[i].type == BASIC_ENEMY
				|| game->enemies[i].type == ENEMY_2
				|| game->enemies[i].type == ENEMY_1 
				|| game->enemies[i].type == BOSS)) {
			for (auto& player : game->players) {
				player.on_collision(&game->enemies[i], game);
			}
		}
	}
}

void	prune_inactive(Game *game)
{
	game->bullets.erase(
		std::remove_if(game->bullets.begin(), game->bullets.end(), 
			[](Entity& object){ 
				if (object.status == false || object.current_pos.y < 0 || object.current_pos.x < 0 || object.current_pos.y >=   map_height || object.current_pos.x >= map_width)
					return (true);
				else
					return (false);
			}), 
		game->bullets.end());

	game->enemies.erase(
		std::remove_if(game->enemies.begin(), game->enemies.end(), 
			[](Entity& object){ 
				if (object.status == false || object.current_pos.y < 0 || object.current_pos.x < 0 || object.current_pos.y >=   map_height || object.current_pos.x >= map_width)
					return (true);
				else
					return (false);
			}), 
		game->enemies.end());

	game->background.prune();
}

bool	check_terminal_size(Game *game)
{
	int y;
	int x;

	getmaxyx(stdscr, y, x);
	while (y < game->term_height || x < game->term_width)
	{
		clear();
		mvprintw(0, 0, "TERMINAL TOO SMALL");
		mvprintw(1, 0, "  minimum: %dx%d", game->term_height, game->term_width);
		mvprintw(2, 0, "  current: %dx%d", y, x);
		nodelay(stdscr, FALSE);
		int input = tolower(getch());
		if (input == 'q' || input == KEY_ESCAPE)
			return false;
		delete_win(game);
		getmaxyx(stdscr, y, x);
	}
	init_win(game);
	nodelay(stdscr, TRUE);
	return (true);
}

bool	game_loop(Game *game)
{
	long	time_reference = get_current_time();
	game->start_time = get_current_time_in_seconds();
	nodelay(stdscr, TRUE);
	srand(time(NULL));
	//spawn_entities(game);
	wclear(game->status_win);
	game->score = 0;
	while (1)
	{
		if ((float)(get_current_time() - time_reference) > (float)1000 / FPS)
		{
			time_reference = get_current_time();
			int input = tolower(getch());
			if (input == 'q' || input == KEY_ESCAPE)
				return false;
			if (input == 'r' && shared_players_hp(game) <= 0)
				return true;
			if (input == KEY_RESIZE)
			{
				if (!check_terminal_size(game))
				 return false;
			}
			else 
			{
				for (auto& player : game->players) {
					if (player.update(input, game)) {
						break;
					}
				}
			}
			update_entities(game);
			check_collisions(game);
			prune_inactive(game);
			spawn_entities(game);
			game->background.update();
			if (shared_players_hp(game) <= 0)
			{
				if (game->gameover_time == 0) {
					game->gameover_time = get_current_time_in_seconds();
				}
			}
			print_stuff(game);
		}
		else
			usleep (1000);
	}
}

void	init_players(int amount, Game *game)
{
	Coordinate start = {(map_width / 2) - 3,  map_height / 2};
	const int spacing = 4;

	start.y -= (spacing / 2) * (amount - 1);

	for (int i = 0; i < amount; ++i) {
		game->players.emplace_back(i, start);
		start.y += spacing;
	}
}

bool set_map_size()
{
	int term_height;
	int term_width;
	getmaxyx(stdscr, term_height, term_width);

	while (term_height < MIN_TERMINAL_HEIGHT || term_width < MIN_TERMINAL_WIDTH)
	{
		clear();
		mvprintw(0, 0, "TERMINAL TOO SMALL");
		mvprintw(1, 0, "  minimum: %dx%d", MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH);
		mvprintw(2, 0, "  current: %dx%d", term_height, term_width);
		refresh();
		int input = tolower(getch());
		if (input == 'q' || input == KEY_ESCAPE)
			return (false);
		getmaxyx(stdscr, term_height, term_width);
	}
	map_height = term_height - STATUS_WINDOW_HEIGHT - 2;
	map_width = (term_width / 2) - 2;
	return (true);
}

int	menu()
{
	static int i = 1;
	while (1)
	{
		wattr_on(stdscr, A_BOLD, 0);
		if (i == 1)
		{
			wattr_on(stdscr, A_REVERSE, 0);
			mvprintw(0, 0, "Single Player ");
			wattr_off(stdscr, A_REVERSE, 0);
			mvprintw(1, 0, "Multiplayer ");
		}
		else
		{
			mvprintw(0, 0, "Single Player ");
			wattr_on(stdscr, A_REVERSE, 0);
			mvprintw(1, 0, "Multiplayer ");
			wattr_off(stdscr, A_REVERSE, 0);
		}
		wattr_off(stdscr, A_BOLD, 0);
		int input = tolower(getch());
		if (input == 'q' || input == KEY_ESCAPE)
			return -1;
		if (input == 'w' || input == KEY_UP || input == 's' || input == KEY_DOWN)
			i *= -1;
		if (input == '\n' || input == ' ')
		{
			if (i == 1)
				return (1);
			else
				return (2);
		}
	}
}

int main()
try {
	if (!init_ncurses())
		return (1);
	bool keep_playing = true;
	while (keep_playing)
	{
		int player_count = menu();
		if (player_count == -1 || !set_map_size())
			break;
		Game game;
		init_win(&game);
		init_players(player_count, &game);
		print_stuff(&game);
		keep_playing = game_loop(&game);
		delete_win(&game);
	}
	endwin();
	return (0);
} 
catch (std::exception& e) {
	std::cerr << ft::log::error(e.what()) << '\n';
	return (1);
}
