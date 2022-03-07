//
// Created by Peer De bakker on 3/7/22.
//

#ifndef CLUSTER_MOVE_H
#define CLUSTER_MOVE_H

typedef enum movetype {
	DROP = 0,
	ROTATE = 1,
	ERROR = 2
}	e_movetype;

typedef struct s_move {
	e_movetype	type;
	int			value;
}	t_move;


// srcs/move/move.c
t_move	error_move();
void	print_move(int fd, const t_move *move);

#endif //CLUSTER_MOVE_H
