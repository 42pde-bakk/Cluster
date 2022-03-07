/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 11:27:50 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/07 15:32:23 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_PROCESS_H
#define CLUSTER_PROCESS_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

# include "cluster.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

#define MAX_PLAYER 2

typedef struct s_player
{
	pid_t pid;
	int stdin[2];
	int stdout[2];
	FILE* reader;
	int col1;
	int col2;
	size_t amount1;
	size_t amount2;
} t_player;

int init_player_process(const char* path, t_player* player);


typedef struct s_players {
    t_player    p[2];
    bool        turn;
}   t_players;

t_players       *init_players(int ringsize);
const t_tile    *play_turn(bool turn, t_players *players);

#endif
