#include "cluster.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	bool	player_turn = 0;
	int		ringsize = 5;

	t_players *players = init_players(ringsize);
	init_field();
	while (1)
	{
		printf("turn: %d\n", player_turn);

		//print grid to show options for player
    	print_grid_terminal(players->p[turn].col1, players->p[turn].col2);

		//player plays their turn
		play_turn(player_turn, players);

		//check if there is a winner

		//change turn to the next player
		player_turn = !player_turn;	
	}
	return 0;
}
