/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:27:50 by jaberkro          #+#    #+#             */
/*   Updated: 2022/03/08 11:58:37 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_PLAYER_H
#define CLUSTER_PLAYER_H

#include <stdio.h>
#include <assert.h>
#include <time.h>
# include "cluster.h"
#include "move.h"

#define MAX_PLAYER 2

typedef struct s_player
{
	pid_t pid;
	int stdin[2];
	int stdout[2];
	FILE* reader;

	int		col[2];
	size_t	amount[2];
} t_player;

typedef struct s_players {
    t_player    p[2];
    bool        turn;
}   t_players;

// srcs/player/input.c
t_move	player_request_input(t_player *player);
// srcs/player/process.c
int init_player_process(const char* path, t_player* player);

// srcs/player/player.c
t_players       *init_players(int ringsize);

// srcs/player/inventory.c
int		bag_amount_check(t_player *player);
void	generate_random_colours(t_player *player, int *col_a, int *col_b);
int		update_inventory(t_player* player, int colour_index);

#endif
