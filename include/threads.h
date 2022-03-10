//
// Created by Peer De bakker on 3/10/22.
//

#ifndef CLUSTER_THREADS_H
#define CLUSTER_THREADS_H

#include <pthread.h>
#include "player.h"

extern int				game_alive;
extern pthread_mutex_t	mutex_state;
extern pthread_mutex_t	mutex_draw;
extern pthread_mutex_t	mutex_read;

extern pthread_t		thread_draw;

typedef struct s_drawinfo {
	bool	can_draw;
	int 	col1,
			col2;
	const t_player *player;
}	t_drawinfo;

extern t_drawinfo	g_drawinfo;

// srcs/threads.c

void	signal_print(int col1, int col2, const t_player *player);

int	setup_threads();
int	thread_exit();

#endif //CLUSTER_THREADS_H
