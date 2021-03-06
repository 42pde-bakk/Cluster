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
Type your preffered type of color (A/B) followed by a number from 1 - (gridsize * 2 - 1). \
Afterwards you will see a ball drop.\n \
Connect four of these balls to win!\n \
You can use R followed by a number to rotate the board that amount of times clockwise! (between 1 and 5!)\n \
Good luck!\n");
}

static void	congratulate_winner(const t_player *winner, const t_player *loser) {
	printf("Winner: player %s!\n", winner->name);
	printf("Loser: player %s!\n", loser->name);
}

static void	help() {
	print_rules();
	exit(0);
}

static void	error_duplicate_flag() {
	dprintf(STDERR_FILENO, "Error: duplicate flags found. Please make up your mind!\n");
	exit(EXIT_FAILURE);
}

static void	parser(int argc, char **argv) {
//	gameinfo_init("5");
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--help") == 0) {
			help();
		}
		if (strncmp(argv[i], "--size=", 7) == 0) {
			if (g_gameinfo.size != 0)
				error_duplicate_flag();
			gameinfo_init(&argv[i][7]);
		}
		if (strncmp(argv[i], "--connect=", 10) == 0) {
			if (g_gameinfo.connect != 0)
				error_duplicate_flag();
			g_gameinfo.connect = (int)strtol(&argv[i][10], NULL, 10);
		}
	}
	if (g_gameinfo.size == 0)
		gameinfo_init("5");
	if (g_gameinfo.connect == 0) {
		if (g_gameinfo.size >= 5)
			g_gameinfo.connect = 4;
		else
			g_gameinfo.connect = g_gameinfo.size - 1;
	}
}

void	parse_bots(int ac, char **av, t_players *players) {
	int	player_amount = 0;
	struct stat stat_struct;

	for (int i = 1; i < ac && player_amount < MAX_PLAYER + 1; ++i) {
		// check if it doesnt start with -- and that the file exists
		if (strncmp(av[i], "--", 2) != 0 && stat(av[i], &stat_struct) == 0) {
			t_player	*player = &players->p[player_amount];
			init_player_process(av[i], player);
			send_game_info(player);
			player_amount++;
		}
	}
}

int main(int argc, char **argv) {
	size_t	turn = 0;
	int 	winner = -1;

	parser(argc, argv);
	if (g_gameinfo.connect <= 1 || g_gameinfo.connect >= g_gameinfo.size) {
		dprintf(STDERR_FILENO, "Error. Please provide a valid win condition!\n");
		exit(1);
	}
	init_field();
	t_players *players = init_players(g_gameinfo.tiles_amount);
	parse_bots(argc, argv, players);

	while (winner == -1) {
		//print grid to show options for player
		for (int i = 0; i < MAX_PLAYER; ++i) {
			t_player	*player = &players->p[i];
			int winning_colour = 0;
			int col1, col2;

			if (!bag_amount_check(player)) {
				winner = !i;
				break;
			}
			pick_tile_colours(player, &col1, &col2);
			if (player->pid) // player is a bot
				send_turn_info(players, player, turn, col1, col2);
			else
				print_grid_terminal(col1, col2);
			if (player->pid == 0 || (player->pid && players->p[!i].pid))
				print_inventory(player);
#if !ANIMATION
			if (players->p[0].pid && players->p[1].pid) {
				print_grid_terminal(col1, col2);
				print_inventory(player);
				usleep(ANIMATION_USLEEP * 5000);
			}
#else
			if (players->p[0].pid && players->p[1].pid)
				usleep(7500 * ANIMATION_USLEEP);
#endif

			//player plays their turn
			t_move move = player_request_input(player, turn);
			if (move.type == ERROR) {
				winner = !i;
				break;
			}

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
				winning_colour = win_check_this_tile(played_tile, g_gameinfo.connect);
			else if (move.type == ROTATE)
				winning_colour = win_check_all_tiles(g_gameinfo.connect);
			if (played_tile == NULL && (move.type == ALPHA || move.type == BETA)) {
				winner = !i;
				break;
			}
			printf("Placed on board: player %s has %zu and %zu\n", player->name, player->amount[0], player->amount[1]);
			if (winning_colour) {
				// 1 if winning_colour is 3 or 4
				// 0 if winning_colour is 1 or 2
				winner = (winning_colour > 2);
				break;
			}
		}
		turn += 1;
	}
#if !ANIMATION
	print_grid_terminal(-1, -1);
			usleep(10000 * ANIMATION_USLEEP);
#endif
	congratulate_winner(&players->p[winner], &players->p[!winner]);
	gameinfo_dtor();
	free(players);
	exit(0);
}
