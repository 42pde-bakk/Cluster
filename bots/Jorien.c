#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "move.h"
#include <fcntl.h>
#include <time.h>

void	do_move(const int fd, const int gridsize) {
	static const char* moves[] = {"A", "B", "R"};
	int move_type = rand() % 3;
	int move_value;
	if (move_type == ROTATE)
		move_value = rand() % 5 + 1;
	else {
		move_value = rand() % (gridsize * 2 - 1) + 1;
	}
	printf("%s %d\n", moves[move_type], move_value);
	fflush(stdout);
	dprintf(fd, "%s %d\n", moves[move_type], move_value);
}

int main()
{
	int fd = open("bot.log", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRUSR);
	if (fd == -1) {
		dprintf(2, "opening bot.log failed\n");
		return (1);
	}
	int timeout;
	int timeout_turn0;
	scanf("%d %d", &timeout, &timeout_turn0);
	// 37
	int	gridsize;
	int nb_tiles;
	int	win_condition;
	scanf("%d %d %d", &gridsize, &nb_tiles, &win_condition);

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

	// game loop
	while (1) {
		int nb_players;
		scanf("%d", &nb_players);
		for (int i = 0; i < nb_players; i++) {
			int colours[2];
			int amounts[2];
			scanf("%d %d", &colours[0], &amounts[0]);
			scanf("%d %d", &colours[1], &amounts[1]);
		}
		// the game lasts 24 days: 0-23
		int turn;
		// the current amount of played tiles
		int nb_played_tiles = 0;
		int	col1; // playable tile A
		int	col2; // playable tile B
		scanf("%d %d", &turn, &nb_played_tiles);
		scanf("%d %d", &col1, &col2);
		for (int i = 0; i < nb_played_tiles; i++) {
			// location of this tree
			int cell_index;
			// size of this tree: 0-3
			int colour;
			// 1 if this is your tree
			int _is_mine;
			scanf("%d %d %d", &cell_index, &colour, &_is_mine);
		}
		// Write an action using printf(). DON'T FORGET THE TRAILING \n
		// To debug: fprintf(stderr, "Debug messages...\n");

		srand(time(0));
		// ALPHA cellIdx | BETA cellIdx | ROTATE amount
		do_move(fd, gridsize);
	}
	return 0;
}
