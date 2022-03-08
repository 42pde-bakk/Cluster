#include "cluster.h"
#include "player.h"
#include "move.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void print_rules()
{
	printf("Cluster\n\n\
How to play:\n \
Type your preffered type of color (A/B) followed by a number from 1 - 9. \
Afterwards you will see a ball drop.\n \
Connect four of these balls to win!\n \
You can use R followed by a number to rotate the board that amount of times counterclockwise!\n \
Good luck!\n");
}

static void	congratulate_winner(const int winner) {
	printf("Winner: player %d!"
		"\n", winner);
}

static void	help() {
	print_rules();
	exit(0);
}

static void	parser(int argc, char **argv) {
	gameinfo_init("5");
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--help") == 0) {
			help();
		}
		if (strncmp(argv[i], "--size=", 7) == 0) {
			gameinfo_init(&argv[i][7]);
			++i; // to skip past the size
		}
	}
}

void	parse_bots(int ac, char **av, t_players *players) {
	int	player_amount = 0;
	struct stat stat_struct;

	for (int i = 1; i < ac && player_amount < MAX_PLAYER && av[i]; ++i) {
		// check if it doesnt start with -- and that the file exists
		if (strcmp(av[i], "--") != 0 && stat(av[i], &stat_struct) == 0) {
			t_player	*player = &players->p[i - 1];
			init_player_process(av[i], player);
			send_game_info(player);
		}
	}
}

int main(int argc, char **argv) {
	size_t	turn = 0;
	int 	winner = -1;

	parser(argc, argv);
	init_field();
	printf("created field\n");
	printf("corners[0]:\n");
	print_tile(g_field.corners[0]);
	t_players *players = init_players(g_gameinfo.tiles_amount);
	parse_bots(argc, argv, players);

	while (winner == -1) {
		//print grid to show options for player
		for (int i = 0; i < MAX_PLAYER; ++i) {
			t_player	*player = &players->p[i];
			int winning_colour = 0;
			int col1, col2;

			print_grid_terminal(-1, -1);
			if (!bag_amount_check(player)) {
				winner = !i;
				break;
			}
			pick_tile_colours(player, &col1, &col2);
			if (player->pid) // player is a bot
				send_turn_info(player, turn, col1, col2);
			else
				print_grid_terminal(col1, col2);

			//player plays their turn
			t_move move = player_request_input(player);
			if (move.type == ERROR) {
				winner = !i;
				break;
			}
			print_move(2, &move);
			if (move.type == ALPHA || move.type == BETA) {
				// update inventory
				update_inventory(player, &move, col1, col2);
				if (move.colour <= 0) {
					winner = !i;
					break;
				}
			}
			const t_tile *played_tile = execute_move(&move);
			if ((move.type == ALPHA || move.type == BETA) && played_tile)
				winning_colour = win_check_this_tile(played_tile, g_gameinfo.size - 1);
			else if (move.type == ROTATE)
				winning_colour = win_check_all_tiles(g_gameinfo.size - 1);
			if (winning_colour) {
				// 1 if winning_colour is 3 or 4
				// 0 if winning_colour is 1 or 2
				winner = (winning_colour > 2);
				break;
			}
		}
		turn += 1;
	}
	congratulate_winner(winner);
	gameinfo_dtor();
	free(players);
	return 0;
}
