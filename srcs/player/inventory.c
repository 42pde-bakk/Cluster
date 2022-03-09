/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:24:29 by jaberkro          #+#    #+#             */
/*   Updated: 2022/03/08 12:19:31 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "player.h"
#include <assert.h>
#include <string.h>

int	bag_amount_check(t_player *player) {
	return (player->amount[0] + player->amount[1] != 0);
}

static int	pick_tile_colour(t_player *player) {
	int picked_col,
		other_col;

	picked_col = rand() % 2;
	other_col = !picked_col;
	if (player->amount[picked_col] > 0) {
		player->amount[picked_col] -= 1;
		return (player->col[picked_col]);
	}
	else if (player->amount[other_col] > 0) {
		player->amount[other_col] -= 1;
		return (player->col[other_col]);
	}
	return (0);
}

void	pick_tile_colours(t_player *player, int *col_a, int *col_b) {
	srand(time(0));
	*col_a = pick_tile_colour(player);
	*col_b = pick_tile_colour(player);
}

int update_inventory(t_player *player, t_move *move, int col1, int col2) {
	 player->amount[(move->type + 1) % 2]++;
	 if (move->type == ALPHA)
		 move->colour = col1;
	 else
		 move->colour = col2;
 	return (0);
}
