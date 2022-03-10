//
// Created by Peer De bakker on 3/5/22.
//

#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "move.h"
#include "gameinfo.h"
#include "utils.h"

#ifndef TIME_OUT
# define TIME_OUT 50 // ms
#endif

#ifndef ANIMATION
# define ANIMATION 1
#endif
#ifndef ANIMATION_USLEEP
# define ANIMATION_USLEEP 20
#endif

typedef struct s_player	t_player;

typedef struct s_tile {
	int		idx;
	int		tile_colour;

	struct s_tile	*neighbours[6];
}	t_tile;

typedef struct	s_field {
	int		gravity;
	t_tile	*corners[6];
	t_tile	*center;
	int		number_played_tiles;
}	t_field;

// sicke globals
extern t_field	g_field;
// other globals I put in gameinfo.h

// srcs/field/init_field.c
int	init_field();

// srcs/field/dead_tiles.c
void	spawn_dead_tiles();

// srcs/field/tile.c
int		get_n(const t_tile *t, int dir);
void	print_tile(const t_tile *t);
t_tile	*create_tile();

// srcs/field/directions.c
int	get_previous_direction(int dir);
int get_next_direction(int dir);
int get_opposite_direction(int dir);
int get_link_direction(int dir);
int	direction_add(int dir, int add);

// output/print_grid_terminal.c
void    print_grid_terminal(int opta, int optb);
void	print_inventory(const t_player *player);

// srcs/field/tileorder.c
void	get_indices();

// srcs/field.rotate.c
const t_tile *rotate_field(const t_move *move);

// srcs/field/drop_tile.c
const t_tile *drop_downwards(t_tile *tile);
const t_tile *get_drop_tile(const t_move *move);

// srcs/output/generate.c
char *generated_map(int len);

//winning fucncs
int	win_check_all_tiles(int set_row_length);
int	win_check_this_tile(const t_tile *current_tile, int set_row_length);

#endif //CLUSTER_CLUSTER_H
