//
// Created by Peer De bakker on 3/5/22.
//

#include "cluster.h"

t_field g_field;
t_tile	**tile_arr;


// a is the source tile
// b is the newly created tile
// direction is the dir from a to b
void	link_neighbours(t_tile* a, t_tile* b, const int direction) {
	// link forwards
	const int next_dir = get_next_direction(direction);
	t_tile	*neighbour = a->neighbours[next_dir];
	if (neighbour) {
		int link_dir = get_next_direction(next_dir);
		b->neighbours[link_dir] = neighbour;
		neighbour->neighbours[get_opposite_direction(link_dir)] = b;
	}
	const int prev_dir = get_previous_direction(direction);
	neighbour = a->neighbours[prev_dir];
	if (neighbour) {
		int link_dir = get_previous_direction(prev_dir);
		b->neighbours[link_dir] = neighbour;
		neighbour->neighbours[get_opposite_direction(link_dir)] = b;
	}
}

void	connect_tiles(t_tile* a, t_tile* b, const int direction) {
	// direction is inbetween 0 and 5
	const int opposite_direction = get_opposite_direction(direction);

	a->neighbours[direction] = b;
	if (!b)
		return;
	b->neighbours[opposite_direction] = a;
}

void	set_corners() {
	for (int i = 0; i < 6; ++i)
		g_field.corners[i] = g_field.center->neighbours[i];
}

void	spawn_new_ring(const size_t ringsize) {
	t_tile *first_oldcorner = g_field.corners[0];
	// pak de bovenste tile
//	int x = 0;
	for (int x = 0; x < 6; ++x) {
		t_tile	*start = g_field.corners[x];
		g_field.corners[x] = create_tile();
		connect_tiles(start, g_field.corners[x], x);
		link_neighbours(start, g_field.corners[x], x);

		for (int walk = 0; walk < (int)ringsize - 2; ++walk) {
			// huisje
			int x1 = (x + 1) % 6;
			t_tile	*huisje = create_tile();
			connect_tiles(start, huisje, x1);
			link_neighbours(start, huisje, x1);

			start = start->neighbours[(x + 2) % 6];
		}
	}
	link_neighbours(first_oldcorner, g_field.corners[0], 0);
}

int	create_first_ring() {
	for (int dir = 0; dir < 6; ++dir) {
		t_tile *new_tile = create_tile();
		connect_tiles(g_field.center, new_tile, dir);
		link_neighbours(g_field.center, new_tile, dir);
	}
	set_corners();
	// TODO: still need to connect the invididual new tiles with each other --> this is done now
	return (0);
}

int	init_field() {
	g_field.gravity = 3;
	g_field.number_played_tiles = 0;

	g_field.center = create_tile();
	create_first_ring();
	for (int size = 3; size < g_gameinfo.size + 1; ++size) {
		spawn_new_ring(size);
	}
#ifndef VANILLA
	spawn_dead_tiles();
#endif

	// only if not vanilla
	return (0);
}
