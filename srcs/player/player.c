/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 11:32:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/07 15:31:00 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cluster.h"

t_player init_player(int col1, int col2, int ringsize)
{
    t_player    player;
    size_t      amount = get_size(ringsize) / 4;

    player.col1 = col1;
    player.col2 = col2;
    player.amount1 = amount;
    player.amount2 = amount;
    return (player);
}

t_players   *init_players(int ringsize)
{
    t_players   *players = calloc(1, sizeof(t_players));

    players->p[0] = init_player(1, 2, ringsize);
    players->p[1] = init_player(3, 4, ringsize);
    players->turn = 0;
    return (players);
}
