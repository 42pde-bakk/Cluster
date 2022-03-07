#include "cluster.h"
#include "player.h"
#include "move.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int		ringsize = 5;
	int 	winner = -1;
	int		winning_row_length = 4;

	(void)argc;
	t_players *players = init_players(ringsize);
	for (int p = 0; p < MAX_PLAYER && argv[p + 1]; ++p) {
		init_player_process(argv[p + 1], &players->p[p]);
	}
	init_field();
	while (winner == -1) {
		//print grid to show options for player
		for (int p = 0; p < MAX_PLAYER; ++p) {
			dprintf(2, "p = %d\n", p);
			int winning_colour = 0;
			int col1, col2;

			generate_random_colours(&players->p[p], &col1, &col2);
			print_grid_terminal(col1, col2);
			printf("col1=%d, col2=%d\n", col1, col2);

			//player plays their turn
			t_move move = player_request_input(&players->p[p]);
			if (move.type == ALPHA || move.type == BETA) {
				// update inventory
				update_inventory(&players->p[p], (int)move.type);
				move.colour = players->p[p].col[move.type];
			}
			const t_tile *played_tile = execute_move(&move);
			if ((move.type == ALPHA || move.type == BETA) && played_tile)
				winning_colour = win_check_this_tile(played_tile, winning_row_length);
			else if (move.type == ROTATE)
				winning_colour = win_check_all_tiles(winning_row_length);
			printf("after winning check\n");
			if (winning_colour) {
				// 1 if winning_colour is 3 or 4
				// 0 if winning_colour is 1 or 2
				winner = (winning_colour > 2);
				printf("Winner: player %d\n", winner);
				break;
			}
		}
	}
	return 0;
}
