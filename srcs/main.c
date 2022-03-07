#include "cluster.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	bool	player_turn = 0;
	int		ringsize = 5;
	const t_tile	*newtile = NULL;

	t_players *players = init_players(ringsize);
	init_field();
	while (1)
	{
		//print grid to show options for player
    	print_grid_terminal(players->p[player_turn].col1, players->p[player_turn].col2);

		//player plays their turn
		newtile = play_turn(player_turn, players);

		//check if there is a winner
		if (newtile == NULL)
			printf("last turn we rotated\n");
		else
			printf("last turn we inserted a new tile\n");

		//change turn to the next player
		player_turn = !player_turn;	
	}
	return 0;
}
