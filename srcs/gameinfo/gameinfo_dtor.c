//
// Created by Peer De bakker on 3/8/22.
//

#include "gameinfo.h"
#include <stdlib.h>

void	gameinfo_dtor(void) {
	for (int i = 0; i < g_gameinfo.tiles_amount; i++) {
		free(tile_arr[i]);
		tile_arr[i] = NULL;
	}
	free(tile_arr);
	tile_arr = NULL;
	free(tile_order);
	tile_order = NULL;
}
