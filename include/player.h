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

#ifndef PLAYER_H
# define PLAYER_H

# include "cluster.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_player {
    int col1;
    int col2;
    size_t amount1;
    size_t amount2;
}   t_player;

typedef struct s_players {
    t_player    p[2];
    bool        turn;
}   t_players;

t_players       *init_players(int ringsize);
const t_tile    *play_turn(bool turn, t_players *players);

#endif