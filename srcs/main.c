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

int main(int argc, char **argv) {
	int		ringsize = 5;
	int 	winner = -1;
	int		winning_row_length = 4;
	int i = 0;

	(void)argc;
	if (argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		print_rules();
		exit(0);
	}
	t_players *players = init_players(ringsize);
	for (int p = 0; p < MAX_PLAYER && argv[p + 1]; ++p) {
		init_player_process(argv[p + 1], &players->p[p]);
	}
	init_field();
	while (winner == -1) {
		//print grid to show options for player
		for (int p = 0; p < MAX_PLAYER; ++p) {
			dprintf(2, "It is the turn of player %d\n", p);
			int winning_colour = 0;
			int col1, col2;

			if (!bag_amount_check(&players->p[p])) {
				printf("Winner: player %d\n", (p + 1) % 2);
				break;
			}
			generate_random_colours(&players->p[p], &col1, &col2);
			print_grid_terminal(col1, col2);
			printf("col1=%d, col2=%d\n", col1, col2);

			//player plays their turn
			t_move move = player_request_input(&players->p[p]);
			if (move.type == ALPHA || move.type == BETA) {
				// fix this to put MAX 1 item back into the bag
				// and set move.colour to the wanted one
				players->p[p].amount[(move.type + 1) % 2]++;
				//update_inventory(&players->p[p], (int)move.type);
				if (move.type == ALPHA)
					move.colour = col1;
				else
					move.colour = col2;
				// move.colour = players->p[p].col[move.type];
			}
			const t_tile *played_tile = execute_move(&move);
			if ((move.type == ALPHA || move.type == BETA) && played_tile)
				winning_colour = win_check_this_tile(played_tile, winning_row_length);
			else if (move.type == ROTATE)
				winning_colour = win_check_all_tiles(winning_row_length);
			printf("after winning check\n Here some more info\n");
			make_dead_tiles(tile_arr);
			while (tile_arr[i]) {
				printf("%d\n", tile_arr[i]->alive);
				i++;
			}
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
