/* Created by jaberkro on march 5th 22. */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cluster.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define GRY   "\x1B[90m"
#define RESET "\x1B[0m"

void    print_grid_terminal()
{
    FILE *grid = fopen("maps/grid5.txt", "r");
    get_indices(get_opposite_direction(g_field.gravity));
    char	*items[5] = { WHT"{}"RESET, RED"##"RESET, YEL"@@"RESET, BLU"$$"RESET, CYN"&&"RESET };
    char    c;
    int     i = 0;
    
    while (1)
    {
        c = (char)getc(grid);
        if (c == '.')
            break;
        else if (c == '}')
            ;
        else if (c == '{')
        {
            printf("%s", items[tile_arr[tile_order[i]]->tile_colour]);
            i++;
        }
        else if (c == '|' || c == 'v')
            printf(GRY "%c", c);
        else if (c == 'A') {
            printf(RED "%c" RESET, c);
        }
        else if (c == 'B') {
            printf(BLU "%c" RESET, c);
        }
        else
            printf(WHT "%c", c);
    }
    printf("\n");
}