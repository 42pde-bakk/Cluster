/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 11:32:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/07 12:21:19 by jaberkro      ########   odam.nl         */
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

t_players   *create_players(int ringsize)
{
    t_players   *players = calloc(1, sizeof(t_players));

    players->p[0] = init_player(1, 2, ringsize);
    players->p[1] = init_player(3, 4, ringsize);
    players->turn = 0;
    return (players);
}

// int main(void)
// {
//     t_players *players = create_players(5);

//     printf("[%d, %d, %zu, %zu]\n", players->p[0].col1, players->p[0].col2, players->p[0].amount1, players->p[0].amount2);
//     printf("[%d, %d, %zu, %zu]\n", players->p[1].col1, players->p[1].col2, players->p[1].amount1, players->p[1].amount2);
//     //printf("[%d, %d, %zu, %zu]\n", players->player2.col1, players->player2.col2, players->player2.amount1, players->player2.amount2);
//     return (0);
// }

