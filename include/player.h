//
// Created by Peer De bakker on 3/7/22.
//

#ifndef CLUSTER_PLAYER_H
#define CLUSTER_PLAYER_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_PLAYER 2

typedef struct s_player
{
	pid_t pid;
	int stdin[2];
	int stdout[2];
	FILE* reader;
} t_player;

int init_player(const char* path, t_player* player);

#endif //CLUSTER_PLAYER_H
