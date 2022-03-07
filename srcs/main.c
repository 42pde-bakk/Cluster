#include "cluster.h"
#include <stdio.h>
#include <string.h>

int main() {
	char	command[10];
	int		nb;
	char	col1;
	char	col2;
	bool	player = 0;
	(void)col2;

	init_field();
	while (1)
	{
		//who's turn is it? Player 0 has colors red and yellow, player 1 has colors green and blue. This whould be done by a function that gives 4 different options later : r r || r y || y r || y y etc
		if (player == 0)
		{
			col1 = 'r';
			col2 = 'y';
		}
		else
		{
			col1 = 'b';
			col2 = 'g';
		}
		//read command
		print_grid_terminal(col1, col2);
		bzero(command, sizeof(command));
		scanf("%s %d", command, &nb);
		//if the command given starts with A, B or R, see it as a valid command and (later: update the field), print the field and change the turn to the other player
		if (strncmp(command, "D", 1) == 0) {
			get_drop_tile(nb, player *2 + 1);
			// player 0 will drop colour 1 or 2 (0 = empty)
			// player 1 will drop colour 3 or 4
		}
		else if (strncmp(command, "R", 1) == 0) {
			printf("in here!\n");
			rotate_field(nb);
		}
		player = !player;
		// if (strncmp(command, "A", 1) == 0 || strncmp(command, "B", 1) == 0 || strncmp(command, "R", 1) == 0)
		// {
		// 	print_grid_terminal(col1, col2);
		// 	player = !player;
		// }
		
	}
	// print to show it works

//	while (game_alive()) {
//		ask_input();
//		calculate_game_state();
//		print_or_return_output();
//	}
	return 0;
}
