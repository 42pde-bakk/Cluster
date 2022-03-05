#include "cluster.h"
#include <stdio.h>
#include <string.h>

int main() {
	char	command[3];
	char	col1;
	char	col2;
	bool	player = 0;

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
		scanf("%s", command);
		//if the command given starts with A, B or R, see it as a valid command and (later: update the field), print the field and change the turn to the other player
		if (strncmp(command, "A", 1) == 0 || strncmp(command, "B", 1) == 0 || strncmp(command, "R", 1) == 0)
		{
			print_grid_terminal(col1, col2);
			player = !player;
		}
		
	}
	// print to show it works

//	while (game_alive()) {
//		ask_input();
//		calculate_game_state();
//		print_or_return_output();
//	}
	return 0;
}
