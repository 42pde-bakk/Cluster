/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile_colour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:46:26 by tbouma            #+#    #+#             */
/*   Updated: 2022/03/07 14:37:35 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"

int neighbour_colour_check(const t_tile *current_tile, int direction)
{
	if (current_tile->neighbours[direction]) {
		if (current_tile->tile_colour == current_tile->neighbours[direction]->tile_colour)
			return (1);
	}
	return (0);
}

int direction_check(const t_tile *current_tile, int direction)
{
	int	number_of_same_tiles = 0;
	
	while (current_tile && neighbour_colour_check(current_tile, direction)) {
		number_of_same_tiles++;
		current_tile = current_tile->neighbours[direction];
	}
	return (number_of_same_tiles);
}

int	win_check_this_tile(const t_tile *current_tile, int set_row_length) {
	int direction = 0;	
	
	while (direction < 3) {
		int nb = 1 + direction_check(current_tile, direction) +
				direction_check(current_tile, get_opposite_direction(direction));
		if (nb >= set_row_length) {
			// 4 in a row, there is a winner!
			return (current_tile->tile_colour);			
		}
		direction++;
	}
	return (0);
}

int	win_check_all_tiles(int set_row_length) {
	int i = 0;
	while (tile_arr[i])
	{
		if (tile_arr[i]->tile_colour)
		{
			if (win_check_this_tile(tile_arr[i], set_row_length))
				return (tile_arr[i]->tile_colour);
		}
		i++;
	}
	return (0);
}
