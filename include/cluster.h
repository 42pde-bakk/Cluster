//
// Created by Peer De bakker on 3/5/22.
//

#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

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

extern t_field g_field;
extern t_tile	*tile_arr[100];

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
void    print_grid_terminal(char col1, char col2);

#endif //CLUSTER_CLUSTER_H
