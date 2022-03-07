#include "cluster.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

int main() {
	//char	command[3];
	//int		nb;

	bool	player_turn = 0;
	int		ringsize = 5;

	t_players *players = init_players(ringsize);
	init_field();
	while (1)
	{
		printf("turn: %d\n", player_turn);
		play_turn(player_turn, players);
		//check of gewonnen
		player_turn = !player_turn;
		//read command
		//print_grid_terminal(players->p[player_turn].col1, players->p[player_turn].col2);
		// bzero(command, sizeof(command));
		// scanf("%c%d", command, &nb);
		// //if the command given starts with A, B or R, see it as a valid command and (later: update the field), print the field and change the turn to the other player
		// if (strncmp(command, "D", 1) == 0) {
		// 	get_drop_tile(nb, player *2 + 1);
		// 	// player 0 will drop colour 1 or 2 (0 = empty)
		// 	// player 1 will drop colour 3 or 4
		// }
		// else if (strncmp(command, "R", 1) == 0) {
		// 	printf("in here!\n");
		// 	rotate_field(nb);
		// }
		// player = !player;
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
