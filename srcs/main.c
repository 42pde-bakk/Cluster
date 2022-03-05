#include "cluster.h"
#include <stdio.h>

int main() {
	init_field();

	print_grid_terminal('a', 'b');
	printf("\n");
	// print to show it works

//	while (game_alive()) {
//		ask_input();
//		calculate_game_state();
//		print_or_return_output();
//	}
	return 0;
}

//gcc main.c -I ../include field/*.c ../output/*.c                                                                                                       master 