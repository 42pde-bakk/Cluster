#include "cluster.h"
#include "player.h"
#include "move.h"
#include <stdio.h>
#include <string.h>

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
	printf("Winner: player %d\n", winner);
}

int main(int argc, char **argv) {
	size_t	turn = 0;
	int		ringsize = 5;
	int 	winner = -1;
	int		winning_row_length = 4;

	(void)argc;
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		print_rules();
		exit(0);
	}
	init_field();
	t_players *players = init_players(ringsize);
	for (int p = 0; p < MAX_PLAYER && argv[p + 1]; ++p) {
		init_player_process(argv[p + 1], &players->p[p]);
		send_game_info(&players->p[p]);
	}
	while (winner == -1) {
		//print grid to show options for player
		for (int i = 0; i < MAX_PLAYER; ++i) {
			t_player	*player = &players->p[i];
			int winning_colour = 0;
			int col1, col2;

			if (!bag_amount_check(player)) {
				printf("Winner: player %d\n", (i + 1) % 2);
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
				continue;
			}
			print_move(2, &move);
			if (move.type == ALPHA || move.type == BETA) {
				// update inventory
				update_inventory(player, &move, col1, col2);
				if (move.colour <= 0) {
					winner = !i;
					continue;
				}
			}
			const t_tile *played_tile = execute_move(&move);
			if ((move.type == ALPHA || move.type == BETA) && played_tile)
				winning_colour = win_check_this_tile(played_tile, winning_row_length);
			else if (move.type == ROTATE)
				winning_colour = win_check_all_tiles(winning_row_length);
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
	return 0;
}
