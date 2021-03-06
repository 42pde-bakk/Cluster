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
	static		int idx = 0;
	size_t      amount = ringsize / 4;
    t_player    player = {
		.col = { col1, col2 },
		.amount = { amount, amount },
		.idx = idx++
    };
    player.name = (idx == 1) ? "1" : "2";
    player.reader = stdin;
    return (player);
}

t_players   *init_players(int tiles_amount)
{
    t_players   *players = ft_calloc(1, sizeof(t_players));

    players->p[0] = init_player(1, 2, tiles_amount);
    players->p[1] = init_player(3, 4, tiles_amount);
    players->turn = 0;
    return (players);
}
