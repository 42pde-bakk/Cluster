//
// Created by Peer De bakker on 3/9/22.
//

#include "cluster.h"
#include <time.h>

bool	vibe_check(const t_tile* tile) {
	for (short i = 0; i < 6; i++) {
		const t_tile *n = tile->neighbours[i];
		if (n && n->tile_colour == -1)
			return (false);
	}
	// passes the vibe check
	return (true);
}

void	shuffle(int *array, size_t n) {
	if (n <= 1)
		return;
	for (size_t i = 0; i < n - 1; i++) {
		size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
		int t = array[j];
		array[j] = array[i];
		array[i] = t;
	}
}

void	spawn_dead_tiles() {
	int dead_amount;
	int	arr[g_gameinfo.tiles_amount];

	srand(time(0));
	if (rand() % 2) // LETS PLAY VANILLA BROER
		return;
	for (int i = 0; i < g_gameinfo.tiles_amount; ++i)
		arr[i] = i;

	shuffle(arr, g_gameinfo.tiles_amount);

	dead_amount = rand() % g_gameinfo.size + 1;
	srand(time(NULL));
	while (dead_amount) {
		for (int i = 0; i < g_gameinfo.tiles_amount && dead_amount; i++) {
			int check = rand() % (g_gameinfo.tiles_amount / 4);
			if (check < 10 && vibe_check(tile_arr[arr[i]])) {
				dead_amount--;
				tile_arr[arr[i]]->tile_colour = -1;
				print_tile(tile_arr[i]);
			}
		}
	}
}
