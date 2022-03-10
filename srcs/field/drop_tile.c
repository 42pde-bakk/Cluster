//
// Created by Peer De bakker on 3/6/22.
//

#include "cluster.h"
#include <assert.h>
#include <threads.h>

const t_tile *drop_downwards(t_tile *tile) {
    const int   grav = g_field.gravity;
    t_tile      *down = tile->neighbours[grav];

#if ANIMATE
    signal_print(-1, -1, NULL);
//	print_grid_terminal(-1, -1, NULL);
    usleep(200000);
#endif
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
    int start = g_gameinfo.size; // because it's in the middle (check the figure Jorien made)
    int movedirection;
    int delta = 1;
	print_tile(drop_tile);
    if (pos < start) {
        movedirection = get_next_direction(g_field.gravity);
        delta = -1;
    }
    else
        movedirection = get_previous_direction(g_field.gravity);
    
    while (pos != start) {
        drop_tile = drop_tile->neighbours[movedirection];
        start += delta;
    }
    if (drop_tile->tile_colour) {
        // has already been filled
        printf("Damn son, the tile you chose already is filled, what a shitty move!\n");
        return (NULL);
    }
    drop_tile->tile_colour = move->colour;
    ++g_field.number_played_tiles;
    return (drop_downwards(drop_tile));
}

