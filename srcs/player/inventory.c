/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   play_turn.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:24:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/07 15:36:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "player.h"
#include <assert.h>
#include <string.h>

void	generate_random_colours(t_player *player, int *col_a, int *col_b) {
	*col_a = player->col[0];
	*col_b = player->col[1];
}

int	update_inventory(t_player* player, int colour_index) {
	if (player->amount[colour_index] == 0)
		return (1);
	player->amount[colour_index] -= 1;
	return (0);
}

//const t_tile	*play_turn(bool turn, t_players *players)
//{
//	char	command[3000];
//
//	//randomly grab 2 pieces from the player's bag
//
//	// player give input
//	bzero(command, 3000);
//	while ((command[0] != 'A' && command[0] != 'B' && command[0] != 'R' ) || (command[1] - 48 < 0 || command[1] - 48 > 9))
//		scanf("%s", command);
//	//printf("command=%s, turn = %d, colours: %d, %d\n", command, turn, players->p[turn].col1, players->p[turn].col2);
//
//	// work out player input
//	if (command[0] == 'A') {
//		players->p[turn].amount1 -= 1;
//		return
//		return (get_drop_tile(command[1] - 48, players->p[turn].col1));
//	}
//	else if (command[0] == 'B') {
//		players->p[turn].amount2 -= 1;
//		return (get_drop_tile(command[1] - 48, players->p[turn].col2));
//	}
//	else if (command[0] == 'R') {
//		printf("let's rotate!\n");
//		rotate_field(command[1] - 48);
//	}
//	return (NULL);
//}
