#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "move.h"

void	do_move() {
	static const char* moves[] = {"ALPHA", "BETA", "ROTATE"};
	int move_type = rand() % 3;
	int move_value;
	if (move_type == ROTATE)
		move_value = rand() % 5 + 1;
	else
		move_value = rand() % 9 + 1;
	printf("%s %d\n", moves[move_type], move_value);
	dprintf(2, "MOVE: %s %d\n", moves[move_type], move_value);
}

int main()
{
	// 37
	int nb_tiles;
	scanf("%d", &nb_tiles);

	for (int i = 0; i < nb_tiles; i++) {
		// 0 is the center cell, the next cells spiral outwards
		int index;
		// the index of the neighbouring cell for each direction
		int neigh_0;
		int neigh_1;
		int neigh_2;
		int neigh_3;
		int neigh_4;
		int neigh_5;
		scanf("%d %d %d %d %d %d %d", &index, &neigh_0, &neigh_1, &neigh_2, &neigh_3, &neigh_4, &neigh_5);
	}

	dprintf(2, "bot: after initial info\n");
	// game loop
	while (1) {
		// the game lasts 24 days: 0-23
		int turn;
		// the current amount of played tiles
		int nb_played_tiles = 0;
		scanf("%d %d", &turn, &nb_played_tiles);
		for (int i = 0; i < turn; i++) {
			// location of this tree
			int cell_index;
			// size of this tree: 0-3
			int colour;
			// 1 if this is your tree
			int _is_mine;
			int	col1;
			int	col2;
			scanf("%d %d %d %d %d", &cell_index, &colour, &_is_mine, &col1, &col2);
		}
		dprintf(2, "bot: after turn info\n");
		// Write an action using printf(). DON'T FORGET THE TRAILING \n
		// To debug: fprintf(stderr, "Debug messages...\n");

		// ALPHA cellIdx | BETA cellIdx | ROTATE amount
		do_move();
	}
	return 0;
}
