#include "game.hpp"
#include <algorithm>

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_current_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec);
}

game *get_game(void)
{
	static game game{};

	return (&game);
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
	return (true);
}

WINDOW *create_win(int size_y, int size_x , int pos_y, int pox_x)
{
	WINDOW *win = newwin(size_y, size_x, pos_y, pox_x);
	keypad(win, TRUE);
	return (win);
}

void	init_win()
{
	game *game = get_game();
	game->game_win = create_win(GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH, GAME_WINDOW_Y, GAME_WINDOW_X);
	game->status_win = create_win(STATUS_WINDOW_HEIGHT, STATUS_WINDOW_WIDTH, STATUS_WINDOW_Y, STATUS_WINDOW_X);
}

void	print_status(game *game)
{
	//wclear(game->status_win);
	box(game->status_win, 0, 0);
	mvwprintw(game->status_win, 1, 2, " Time: %-30ld Lives: %d Score: %ld",get_current_time_in_seconds() - game->time, game->player.hp, game->score);
	wrefresh(game->status_win);
}

bool	is_bullet(game *game, int y, int x, int type)
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

bool	is_enemy(game *game, int y, int x, int type)
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

/* void	print_character_with(int type)
{

} */

void	print_game(game *game)
{
	// Clear window
	for (int y = 0; y < GAME_WINDOW_HEIGHT; y++)
	{
		for(int x = 0; x < GAME_WINDOW_WIDTH; x++)
		{
			mvwaddwstr(game->game_win, y, x, L" ");
		}
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
	}
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
			wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_MAGENTA), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"——");
			wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_MAGENTA), 0);
		}
		else if (bullet.type == HOMING_BULLET) {
			wattr_on(game->game_win, A_BOLD | COLOR_PAIR(COLOR_RED), 0);
			mvwaddwstr(game->game_win, bullet.current_pos.y + 1, bullet.current_pos.x * 2 + 2, L"● ");
			wattr_off(game->game_win, A_BOLD | COLOR_PAIR(COLOR_RED), 0);
		}
	}
	for (auto& collidable : game->collidables) {
		if (!collidable.status) {
			continue;
		}
	}
	mvwaddwstr(game->game_win, game->player.current_pos.y + 1, game->player.current_pos.x * 2 + 2, L"🛸");

	box(game->game_win, 0, 0);
	wrefresh(game->game_win);
}

void	print_stuff()
{
	game *game = get_game();

	print_game(game);
	print_status(game);
	//refresh();
}

void	spawn_player_bullet(game *game)
{
	if (get_current_time() - game->player.shoot_cooldown > 200)
	{
		game->player.shoot_cooldown = get_current_time();

		entity bullet = {};
		bullet.type = PLAYER_BULLET;
		bullet.status = 1;
		bullet.damage = 1;
		bullet.speed = 1000;
		bullet.current_pos.y = game->player.current_pos.y;
		bullet.current_pos.x = game->player.current_pos.x;
		game->bullets.push_back(bullet);
	}
}

void	spawn_enemy_bullet(game *game, entity *enemy, int bullet_type)
{
	enemy->shoot_cooldown = get_current_time();
	if (rand() % 2 == 0)
		return ;
	entity bullet = {};
	bullet.type = bullet_type;
	bullet.status = 1;
	bullet.damage = 1;
	bullet.speed = 1000;
	bullet.current_pos.y = enemy->current_pos.y;
	bullet.current_pos.x = enemy->current_pos.x;
	game->bullets.push_back(bullet);
}

void	move_p_bullet(entity *bullet)
{
	bullet->move_cooldown = get_current_time();
	bullet->previous_pos = bullet->current_pos;
	bullet->current_pos.x++;
}

void	move_enemy_bullets(game *game, entity *bullet)
{
	bullet->move_cooldown = get_current_time();
	bullet->previous_pos = bullet->current_pos;
	if (bullet->type == HOMING_BULLET && bullet->direction == 0 && game->player.current_pos.y != bullet->current_pos.y && game->player.current_pos.x == bullet->current_pos.x)
	{
		if (game->player.current_pos.y < bullet->current_pos.y)
			bullet->direction = -1;
		else
			bullet->direction = 1;
	}
	if (bullet->type == HOMING_BULLET && bullet->direction != 0)
		bullet->current_pos.y += bullet->direction;
	else
		bullet->current_pos.x--;
}

void	move_enemy(entity *enemy)
{
	enemy->move_cooldown = get_current_time();
	if (enemy->pattern_idx >= enemy->pattern.size())
		enemy->pattern_idx = 0;
	enemy->previous_pos = enemy->current_pos;
	enemy->current_pos.y += enemy->pattern[enemy->pattern_idx].y;
	enemy->current_pos.x += enemy->pattern[enemy->pattern_idx].x;
	enemy->pattern_idx++;
}

void	update_entities(game *game)
{
	for (size_t i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i].status == 1 && game->bullets[i].type == PLAYER_BULLET
			&& get_current_time() - game->bullets[i].move_cooldown > 20)
			move_p_bullet(&game->bullets[i]);
		else if (game->bullets[i].status == 1
			&& ((game->bullets[i].type == ENEMY_BULLET && get_current_time() - game->bullets[i].move_cooldown > 100)
				|| (game->bullets[i].type == HOMING_BULLET && get_current_time() - game->bullets[i].move_cooldown > 180)))
			move_enemy_bullets(game, &game->bullets[i]);
	}
	for (size_t i = 0; i < game->enemies.size(); i++)
	{
		if (game->enemies[i].status == 1 && game->enemies[i].type == BASIC_ENEMY
			&& get_current_time() - game->enemies[i].move_cooldown > 350)
				move_enemy(&game->enemies[i]);
		if (game->enemies[i].status == 1 && game->enemies[i].type == BASIC_ENEMY
			&& get_current_time() - game->enemies[i].shoot_cooldown > 1500)
				spawn_enemy_bullet(game, &game->enemies[i], ENEMY_BULLET);
		if (game->enemies[i].status == 1 && game->enemies[i].type == ENEMY_2
			&& get_current_time() - game->enemies[i].move_cooldown > 350)
				move_enemy(&game->enemies[i]);
		if (game->enemies[i].status == 1 && game->enemies[i].type == ENEMY_2
			&& get_current_time() - game->enemies[i].shoot_cooldown > 2500)
				spawn_enemy_bullet(game, &game->enemies[i], HOMING_BULLET);
	}
}

void	spawn_basic_enemiy(game *game, int y, int x)
{
	entity enemy = {};
	enemy.status = 1;
	enemy.type = BASIC_ENEMY;
	enemy.current_pos.y = y;
	enemy.current_pos.x = x;
	enemy.hp = 1;
	enemy.damage = 1;
	enemy.shoot_cooldown = get_current_time() - rand() % 2000;
	enemy.pattern = {LEFT, DOWN, LEFT, UP};
	game->enemies.push_back(enemy);
}

void	spawn_enemy_2(game *game, int y, int x)
{
	entity enemy = {};
	enemy.status = 1;
	enemy.type = ENEMY_2;
	enemy.current_pos.y = y;
	enemy.current_pos.x = x;
	enemy.hp = 1;
	enemy.damage = 1;
	enemy.shoot_cooldown = get_current_time() + rand() % 1000;
	enemy.pattern = {LEFT, UP, LEFT, DOWN, LEFT, DOWN, LEFT, UP};
	game->enemies.push_back(enemy);
}

void	spawn_entities(game *game)
{
	static int i = 1;
	if (!(get_current_time() - game->enemy_spawn_cooldown > 4000))
		return ;
	game->enemy_spawn_cooldown = get_current_time();
	for (int y = 0; y < MAX_MAP_HEIGHT - 1; y++)
	{
		if (i == 1 && rand() % 2 == 0)
		{
			spawn_basic_enemiy(game, y, MAX_MAP_WIDTH - 1);
			y++;
		}
		else if (i == -1 && rand() % 2 == 0)
		{
			spawn_enemy_2(game, y, MAX_MAP_WIDTH - 1);
			y++;
		}
	}
	i *= -1;
}

void	check_bullet_collision(game *game, entity *entity, int type)
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

void	check_enemy_collision(game *game, entity *entity, int type)
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
			game->enemies[i].status = false;
			entity->status = false;
			return ;
		}
	}
}

void	check_player_collision(game *game, entity *entity)
{
	if (game->player.status == 1
		&& ((game->player.current_pos == entity->current_pos)
		|| (game->player.current_pos == entity->previous_pos
			&& game->player.previous_pos == entity->current_pos)))
	{
		if (get_current_time() - game->player.invis_frames > 1000 || entity->type == BASIC_ENEMY)
		{
				game->player.invis_frames = get_current_time();
				game->player.hp--;
		}
		entity->status = false;
		return ;
	}
}

bool	check_collisions(game *game)
{
	for (size_t i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i].status == 1 && game->bullets[i].type == PLAYER_BULLET)
		{
			check_bullet_collision(game, &game->bullets[i], ENEMY_BULLET);
			check_bullet_collision(game, &game->bullets[i], HOMING_BULLET);
			check_enemy_collision(game, &game->bullets[i], BASIC_ENEMY);
			check_enemy_collision(game, &game->bullets[i], ENEMY_2);
		}
		if (game->bullets[i].status == 1 && (game->bullets[i].type == ENEMY_BULLET || game->bullets[i].type == HOMING_BULLET))
		{
			check_player_collision(game, &game->bullets[i]);
			//check_enemy_collision(game, &game->bullets[i], PLAYER);
		}
		
	}
	for (size_t i = 0; i < game->enemies.size(); i++)
	{
		if (game->enemies[i].status == 1 && (game->enemies[i].type == BASIC_ENEMY || game->enemies[i].type == ENEMY_2))
			check_player_collision(game, &game->enemies[i]);
	}

	game->bullets.erase(
		std::remove_if(game->bullets.begin(), game->bullets.end(), 
			[](entity& object){ 
				if (object.status == false || object.current_pos.y < 0 || object.current_pos.x < 0 || object.current_pos.y >=  MAX_MAP_HEIGHT || object.current_pos.x >= MAX_MAP_WIDTH)
					return (true);
				else
					return (false);
			}), 
		game->bullets.end());

	game->enemies.erase(
		std::remove_if(game->enemies.begin(), game->enemies.end(), 
			[](entity& object){ 
				if (object.status == false || object.current_pos.y < 0 || object.current_pos.x < 0 || object.current_pos.y >=  MAX_MAP_HEIGHT || object.current_pos.x >= MAX_MAP_WIDTH)
					return (true);
				else
					return (false);
			}), 
		game->enemies.end());
	
	return (true);
}

bool	game_loop()
{
	game *game = get_game();
	long	time_reference = get_current_time();
	game->time = get_current_time_in_seconds();
	nodelay(stdscr, TRUE);
	srand(time(NULL));
	//spawn_entities(game);
	wclear(game->status_win);
	while (1)
	{
		if ((float)(get_current_time() - time_reference) > (float)1000 / FPS)
		{
			time_reference = get_current_time();
			int input = getch();
			if (input == 'q' || input == KEY_ESCAPE)
				break ;
			if (input == KEY_RESIZE)
				;//call resize function
			else if (input == 'w' && game->player.current_pos.y != 0)
				game->player.current_pos.y--;
			else if (input == 's' && game->player.current_pos.y != MAX_MAP_HEIGHT - 1)
				game->player.current_pos.y++;
			else if (input == 'd' && game->player.current_pos.x != MAX_MAP_WIDTH - 1)
				game->player.current_pos.x++;
			else if (input == 'a' && game->player.current_pos.x != 0)
				game->player.current_pos.x--;
			else if (input == KEY_SPACE)
				spawn_player_bullet(game);
			update_entities(game);
			check_collisions(game);
			spawn_entities(game);
			if (game->player.hp <= 0)
				break ;
			print_stuff();
		}
		else
			usleep (1000);
		
	}
	return (true);
}

void	init_player()
{
	game *game = get_game();

	game->player.status = 1;
	game->player.current_pos.y = MAX_MAP_HEIGHT / 2;
	game->player.current_pos.x = (MAX_MAP_WIDTH / 2) - 3;
	game->player.hp = 3;

}
int main()
{
	if (!init_ncurses())
		return (1);
	init_win();
	init_player();
	refresh();
	print_stuff();
	game_loop();
	endwin();
	return (0);
	// print
	// input
	// update entities
	// spawn enemies
	//
	// game over check
}
