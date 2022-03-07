#include "cluster.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	bool	player_turn = 0;
	int		ringsize = 5;
	const	t_tile	*played_tile = NULL;
	int		winning_colour;
	int		winning_row_length = 4;

	t_players *players = init_players(ringsize);
	init_field();
	while (1)
	{
		//print grid to show options for player
    	print_grid_terminal(players->p[player_turn].col1, players->p[player_turn].col2);

		//player plays their turn
		played_tile = play_turn(player_turn, players);
		if (played_tile == NULL)
			winning_colour = win_check_all_tiles(winning_row_length);
		else
			winning_colour = win_check_this_tile(played_tile, winning_row_length);
		if (winning_colour)
		{
			printf("winnning colour = %d\n", winning_colour); //return (winning_colour);
			break ;
		}

		//change turn to the next player
		player_turn = !player_turn;	
	}
	return 0;
}
