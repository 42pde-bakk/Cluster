//
// Created by Peer De bakker on 3/6/22.
//

#include "cluster.h"
#include <assert.h>

const t_tile *drop_downwards(t_tile *tile) {
    const int   grav = g_field.gravity;
    t_tile      *down = tile->neighbours[grav];

    print_grid_terminal(-1, -1);
    usleep(200000);
    if (down && down->tile_colour == 0) {
        down->tile_colour = tile->tile_colour;
        tile->tile_colour = 0;
        return (drop_downwards(down));
    }
    return (tile);
}

const t_tile *get_drop_tile(const t_move *move) {
    // assuming 1 is the leftmost drop you can make
	print_move(2, move);
    const int upwards = get_opposite_direction(g_field.gravity);
    int pos = move->value;
    t_tile  *drop_tile = g_field.corners[upwards];
    int start = 5; // because it's in the middle (check the figure Jorien made)
    int movedirection;
    int delta = 1;
	dprintf(2, "drop_tile starts here:\n");
	print_tile(drop_tile);
    if (pos < start) {
        movedirection = get_next_direction(g_field.gravity);
        delta = -1;
    }
    else
        movedirection = get_previous_direction(g_field.gravity);
    
    while (pos != start) {
        printf("pos = %d\n", pos);
        printf("drop_tile: %p, %d, %d\n", (void*)drop_tile, drop_tile->idx, drop_tile->tile_colour);
        drop_tile = drop_tile->neighbours[movedirection];
        start += delta;
    }
    printf("FINAL drop_tile: %p, %d, %d\n", (void*)drop_tile, drop_tile->idx, drop_tile->tile_colour);
    if (drop_tile->tile_colour) {
        // has already been filled
        printf("Damn son, the tile you chose already is filled, what a shitty move!\n");
        return (NULL);
    }
    drop_tile->tile_colour = move->colour;
    ++g_field.number_played_tiles;
    return (drop_downwards(drop_tile));
}

