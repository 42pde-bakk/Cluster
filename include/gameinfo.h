//
// Created by Peer De bakker on 3/8/22.
//

#ifndef CLUSTER_GAMEINFO_H
#define CLUSTER_GAMEINFO_H

//#define TILES_AMOUNT 61
//#define BOARD_SIZE 5
typedef struct s_tile t_tile;

typedef struct s_gameinfo {
	int	size,
		tiles_amount;
}	t_gameinfo;

extern t_gameinfo	g_gameinfo;
extern t_tile	**tile_arr;
extern int		*tile_order;

void	gameinfo_init(const char* size_str);
void	gameinfo_dtor(void);

#endif //CLUSTER_GAMEINFO_H
