//
// Created by Peer De bakker on 3/5/22.
//

#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
	char	value;
	char*	color;
	int		printed;

	struct s_tile	*neighbours[6];
}	t_tile;

typedef struct	s_field {
	int	gravity;
	t_tile	*corners[6];
	t_tile	*center;
}	t_field;

extern t_field g_field;

int	init_field();

// directions.c
int	get_previous_direction(int dir);
int get_next_direction(int dir);
int get_opposite_direction(int dir);
int get_link_direction(int dir);

#endif //CLUSTER_CLUSTER_H
