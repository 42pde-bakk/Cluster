//
// Created by Peer De bakker on 3/5/22.
//

#include "cluster.h"

int	get_n(const t_tile *t, const int dir) {
	if (t->neighbours[dir]) {
		return (t->neighbours[dir]->idx);
	}
	return (-1);
}

void	print_tile(const t_tile *t) {
	if (!t)
		return;
	printf("tile %d, col=%d, neighbours: D:%d, DL:%d, UL:%d, U:%d, UR:%d, DR: %d\n", t->idx, t->tile_colour,
		   get_n(t, 0), get_n(t, 1), get_n(t, 2), get_n(t, 3), get_n(t, 4), get_n(t, 5)
	);
}

t_tile	*create_tile() {
	static int idx = 0;

	t_tile	*tile = calloc(1, sizeof(t_tile));
	if (!tile)
		exit(1);
	tile_arr[idx] = tile;
	tile->idx = idx++;
	tile->tile_colour = 0;
	tile->alive = true;
	return (tile);
}
