//
// Created by Peer De bakker on 3/6/22.
//

#include "cluster.h"
#include <assert.h>
#include <move.h>

t_tile  *bottoms[9];


void    find_bottoms() {
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
    const int antigrav = get_opposite_direction(g_field.gravity);
    bool movement = true;
    while (movement) {
        movement = false;
        for (int i = 0; i < 9; ++i) {
            if (bottoms[i]) {
                movement = true;
                if (bottoms[i]->tile_colour > 0) {
                    drop_downwards(bottoms[i]);
                }
                bottoms[i] = bottoms[i]->neighbours[antigrav];
            }
        }
    }
}

const t_tile * rotate_field(const t_move *move) {
	int value = move->value;
    assert(value > 0 && value < 6);
    // if direction isn't within 1 and 5, this throws an error.
    g_field.gravity = (g_field.gravity + value) % 6;

    printf("gravity now is %d\n", g_field.gravity);

    find_bottoms();
    let_fall();

    // No need to update the corners
    return (NULL); //
}
