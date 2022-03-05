//
// Created by Peer De bakker on 3/5/22.
//

#include "cluster.h"

t_field field;

static t_tile	*create_tile() {
	t_tile	*tile = calloc(1, sizeof(t_tile));
	if (!tile)
		exit(1);
	return (tile);
}

static t_tile	**create_tiles(const size_t amount) {
	t_tile	**tiles = calloc(amount, sizeof(t_tile));
	if (!tiles)
		exit(1);
	return (tiles);
}

void	connect_tiles(t_tile* a, t_tile* b, int direction) {
	// direction is inbetween 0 and 5
	const int opposite_direction = (direction + 3) % 6;

	a->neighbours[direction] = b;
	if (b)
		b->neighbours[opposite_direction] = a;
}

int	create_ring(const size_t ringsize) {
	t_tile	**new_ring = create_tiles(6 * (ringsize - 1));

	for (int dir = 0; dir < 6; ++dir) {
		connect_tiles(field.center, new_ring[dir], dir);
	}
	// TODO: still need to connect the invididual new tiles with each other

}

int	init_field() {
	field.gravity = 1;

	field.center = create_tile();
	create_ring(2);
//6 * (size - 1)
}
