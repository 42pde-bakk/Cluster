/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   play_turn.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:24:29 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/03/07 14:42:27 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "player.h"
#include <assert.h>
#include <string.h>

void play_turn(bool turn, t_players *players)
{
    char command[3000];

    //randomly grab 2 pieces from the player's bag
    
    //print grid to show options for player
    print_grid_terminal(players->p[turn].col1, players->p[turn].col2);

    // let the player choose the input
    bzero(command, 3000);
    scanf("%s", command);
    // if (command[0] != 'A' || command[0] != 'B' || command[0] != 'R' || command[1] - 48 < 0 || command[1] - 48 > 9)
    //     play_turn(turn, players);
    // assert(command[0] == 'A' || command[0] == 'B' || command[0] == 'R');
    // assert(0 < command[1] - 48 && command[1] - 48 < 10);
    printf("command=%s, turn = %d, colours: %d, %d\n", command, turn, players->p[turn].col1, players->p[turn].col2);
    if (command[0] == 'A')
    {
        get_drop_tile(command[1] - 48, players->p[turn].col1);
        players->p[turn].amount1 -= 1;
    }
    else if (command[0] == 'B')
    {
        get_drop_tile(command[1] - 48, players->p[turn].col2);
        players->p[turn].amount2 -= 1;
    }
    else if (command[0] == 'R') {
        printf("let's rotate!\n");
        rotate_field(command[1] - 48);
    }
    else
    {
        play_turn(turn, players);
    }

    // show result
    //print_grid_terminal(players->p[turn].col1, players->p[turn].col2);
}
