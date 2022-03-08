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
	size_t total_amount = player->amount[0] + player->amount[1];
	if (total_amount == 0)
		return (0);
	return (1);
}

void	pick_tile_colours(t_player *player, int *col_a, int *col_b) {
	int picked_colour;

	srand(time(0));
	picked_colour = rand() % 2;
	if (player->amount[picked_colour] > 0) {
		*col_a = player->col[picked_colour];
		player->amount[picked_colour] -= 1;
	}
	else {
		*col_a = player->col[(picked_colour + 1) % 2];
		player->amount[(picked_colour + 1) % 2] -= 1;
	}

	if (player->amount[0] + player->amount[1] == 0) {
		*col_b = 0;
		return;
	}

	picked_colour = rand() % 2;
	if (player->amount[picked_colour] > 0) {
		*col_b = player->col[picked_colour];
		player->amount[picked_colour] -= 1;
	}
	else {
		*col_b = player->col[(picked_colour + 1) % 2];
		player->amount[(picked_colour + 1) % 2] -= 1;
	}
}

int update_inventory(t_player *player, t_move *move, int col1, int col2) {
	 player->amount[(move->type + 1) % 2]++;
	 if (move->type == ALPHA)
		 move->colour = col1;
	 else
		 move->colour = col2;
 	return (0);
}
