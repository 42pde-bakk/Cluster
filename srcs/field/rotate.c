//
// Created by Peer De bakker on 3/6/22.
//

#include "cluster.h"
#include <assert.h>
#include <move.h>
#include "utils.h"

t_tile  **bottoms;

bool	g_movement;

static void    drop_recursive_upwards(t_tile *tile) {
	const int   grav = g_field.gravity;
	const int   antigrav = get_opposite_direction(grav);
	t_tile      *down = tile->neighbours[grav];
	t_tile      *up = tile->neighbours[antigrav];


	if (down && down->tile_colour == 0 && tile->tile_colour > 0) { // dead tiles NOPE
		down->tile_colour = tile->tile_colour;
		tile->tile_colour = 0;
		g_movement = true;
	}
	if (up)
		drop_recursive_upwards(up);
}

static void    find_bottoms() {
    int antigravity = get_opposite_direction(g_field.gravity);
    int left_dir = get_previous_direction(antigravity),
        right_dir = get_next_direction(antigravity);

    t_tile  *left = g_field.corners[g_field.gravity],
            *right = g_field.corners[g_field.gravity];

    for (int i = 0; i < g_gameinfo.size; ++i) {
    	// -1 cus bottoms are indexed 0-8, but labeled 1-9
        bottoms[g_gameinfo.size - 1 - i] = left;
        bottoms[g_gameinfo.size - 1 + i] = right;
        left = left->neighbours[left_dir];
        right = right->neighbours[right_dir];
    }
}

void let_fall(int column_amount) {
	g_movement = true;
    while (g_movement) {
    	g_movement = false;
        for (int i = 0; i < column_amount; ++i) {
        	t_tile	*t = bottoms[i];
            if (t) {
				drop_recursive_upwards(t);
            }
        }
#if ANIMATE
        print_grid_terminal(-1, -1);
		usleep(200000);
#endif
    }
}

const t_tile *rotate_field(const t_move *move) {
	const int column_amount = 2 * g_gameinfo.size + 1;

	bottoms = ft_calloc(column_amount, sizeof(t_tile*));

	int value = move->value;
    g_field.gravity = direction_add(g_field.gravity, -value);


    find_bottoms();
	let_fall(column_amount);

    free(bottoms);
    // No need to update the corners
    return (NULL); //
}
