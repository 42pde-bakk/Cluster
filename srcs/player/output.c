//
// Created by Peer De bakker on 3/7/22.
//

#include "cluster.h"
#include "player.h"

void	send_game_info(const t_player *player) {
	const int fd = player->_stdin[1];

	dprintf(fd, "%d %d\n", g_gameinfo.size, g_gameinfo.tiles_amount);
	for (int i = 0; i < g_gameinfo.tiles_amount; ++i) {
		const t_tile	*t = tile_arr[i];
		dprintf(fd, "%d %d %d %d %d %d %d\n", t->idx, get_n(t, 0), get_n(t, 1), get_n(t, 2), get_n(t, 3), get_n(t, 4), get_n(t, 5));
	}
}

void	send_turn_info(const t_player *player, int turn, int col1, int col2) {
	const int fd = player->_stdin[1];
	int nb_tiles = g_field.number_played_tiles;

	dprintf(fd, "%d %d\n", turn, nb_tiles);
	dprintf(fd, "%d %d\n", col1, col2);
	for (int i = 0; i < g_gameinfo.tiles_amount; ++i) {
		const t_tile *t = tile_arr[i];
		if (t->tile_colour > 0) {
			int _is_mine = (t->tile_colour <= player->idx + 2);
			dprintf(fd, "%d %d %d\n", t->idx, t->tile_colour, _is_mine);
		}
	}
}
