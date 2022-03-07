//
// Created by Peer De bakker on 3/7/22.
//

#ifndef CLUSTER_MOVE_H
#define CLUSTER_MOVE_H

typedef struct s_tile t_tile;

typedef enum movetype {
	ALPHA = 0,
	BETA = 1,
	ROTATE = 2,
	ERROR = 3
}	e_movetype;

typedef struct s_move {
	e_movetype	type;
	int			value;
	int			colour;
}	t_move;


// srcs/move/move.c
t_move	error_move();
void	print_move(int fd, const t_move *move);
const t_tile	*execute_move(const t_move *move);

#endif //CLUSTER_MOVE_H
