//
// Created by Peer De bakker on 3/5/22.
//

#include <assert.h>
#include "cluster.h"

int	*tile_order;
int	write_idx;
int	read_idx;

static bool	not_in_arr(int id) {
	for (int i = 0; i < g_gameinfo.tiles_amount; ++i) {
		if (tile_order[i] == id)
			return (false);
	}
	return (true);
}

void	print_arr() {
	for (int i = 0; i < g_gameinfo.tiles_amount; ++i)
		printf("%d ", tile_order[i]);
	printf("\n");
}

static void	add_to_arr(int left_child_dir, int right_child_dir) {
	int id = tile_order[read_idx];
	++read_idx;
	assert(tile_arr[id]);
	t_tile	*left_neighbour = tile_arr[id]->neighbours[left_child_dir];
	if (left_neighbour && not_in_arr(left_neighbour->idx)) { // get left neighbour
		tile_order[write_idx] = tile_arr[id]->neighbours[left_child_dir]->idx;
		++write_idx;
	}
	t_tile	*right_neighbour = tile_arr[id]->neighbours[right_child_dir];
	if (right_neighbour && not_in_arr(right_neighbour->idx)) { // get left neighbour
		tile_order[write_idx] = tile_arr[id]->neighbours[right_child_dir]->idx;
		++write_idx;
	}
}


static void	clear_arr() {
	for (int i = 0; i < g_gameinfo.tiles_amount; ++i) {
		tile_order[i] = -1;
	}
}

void	get_indices() {
	int antigravity = get_opposite_direction(g_field.gravity);
	int	left_child_dir = get_next_direction(g_field.gravity),
		right_child_dir = get_previous_direction(g_field.gravity);

	clear_arr();
	tile_order[0] = g_field.corners[antigravity]->idx;
	write_idx = 1;
	read_idx = 0;

	for (int i = 0; i < g_gameinfo.tiles_amount; ++i) {
		add_to_arr(left_child_dir, right_child_dir);
	}
}
