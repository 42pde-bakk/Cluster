//
// Created by Peer De bakker on 3/8/22.
//

#include "gameinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

#define MAX_GAMESIZE 100
t_gameinfo	g_gameinfo;


static size_t	get_tile_amount(size_t ringsize) {
	size_t total = 1;

	for (size_t i = 1; i < ringsize; ++i) {
		total += 6 * i;
	}
	return (total);
}

void	gameinfo_init(const char* size_str) {
	const long	size = strtol(size_str, NULL, 10);
	size_t		tile_amount;
	if (size <= 2 || size > MAX_GAMESIZE) {
		dprintf(STDERR_FILENO, "Error. Game size of %ld is invalid, sorry...\n", size);
		exit(EXIT_FAILURE);
	}
	tile_amount = get_tile_amount((size_t)size);
	g_gameinfo.size = (int)size;
	g_gameinfo.tiles_amount = tile_amount;
	tile_arr = ft_calloc(tile_amount + 1, sizeof(t_tile*));
	tile_order = ft_calloc(tile_amount, sizeof(int));
}
