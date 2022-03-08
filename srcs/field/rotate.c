//
// Created by Peer De bakker on 3/6/22.
//

#include "cluster.h"
#include <assert.h>
#include <move.h>

t_tile  *bottoms[9];

t_tile	*falling_tiles[TILES_AMOUNT];

static void    drop_recursive_upwards(t_tile *tile) {
	const int   grav = g_field.gravity;
	const int   antigrav = get_opposite_direction(grav);
	t_tile      *down = tile->neighbours[grav];
	t_tile      *up = tile->neighbours[antigrav];


	if (down && down->tile_colour == 0 && (tile->alive && tile->tile_colour > 0)) { // dead tiles NOPE
		down->tile_colour = tile->tile_colour;
		tile->tile_colour = 0;
//		printf("shifted tile_colour %d from idx %d to idx %d\n", tile->tile_colour, tile->idx, down->idx);
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
    for (int i = 0; i < 5; ++i) {
        bottoms[4 - i] = left;
        bottoms[4 + i] = right;
        left = left->neighbours[left_dir];
        right = right->neighbours[right_dir];
    }
}

void    let_fall() {
    bool movement = true;
    while (movement) {
        movement = false;
        for (int i = 0; i < 9; ++i) {
        	t_tile	*t = bottoms[i];
            if (t) {
                movement = true;
				drop_recursive_upwards(t);
            }
        }
        print_grid_terminal(-1, -1);
		usleep(200000);
    }
}

const t_tile *rotate_field(const t_move *move) {
	int value = move->value;
    assert(value > 0 && value < 6);
    // if direction isn't within 1 and 5, this throws an error.
    g_field.gravity = direction_add(g_field.gravity, -value);

    printf("gravity now is %d\n", g_field.gravity);

    find_bottoms();
    for (int i = 0; i < 9; ++i) {
    	printf("bottoms[%d]: ", i);
    	print_tile(bottoms[i]);
    }
    let_fall();

    // No need to update the corners
    return (NULL); //
}
