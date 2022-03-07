//
// Created by Peer De bakker on 3/5/22.
//

#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define TILES_AMOUNT 61

typedef enum s_dir {
	DOWN = 0,
	DOWNLEFT,
	UPLEFT,
	UP,
	UPRIGHT,
	DOWNRIGHT,
}	t_dir;

typedef struct s_tile {
	int		idx;
	int		tile_colour;
	bool	printed;
	bool	alive;

	struct s_tile	*neighbours[6];
}	t_tile;

typedef struct	s_field {
	int		gravity;
	t_tile	*corners[6];
	t_tile	*center;
}	t_field;


// sicke globals
extern t_field	g_field;
extern t_tile	*tile_arr[TILES_AMOUNT];
extern int		tile_order[TILES_AMOUNT];

// srcs/field/init_field.c
int	init_field();

// srcs/field/tile.c
int	get_n(const t_tile *t, int dir);
void	print_tile(const t_tile *t);
t_tile	*create_tile();

// srcs/field/directions.c
int	get_previous_direction(int dir);
int get_next_direction(int dir);
int get_opposite_direction(int dir);
int get_link_direction(int dir);

// output/print_grid_terminal.c
void    print_grid_terminal();

// srcs/field/tileorder.c
void	get_indices();
size_t	get_size(size_t ringsize);

// srcs/field.rotate.c
void   rotate_field(int direction);

// srcs/field/drop_tile.c
const t_tile *drop_downwards(t_tile *tile);
const t_tile *get_drop_tile(int pos, int colour);

#endif //CLUSTER_CLUSTER_H
