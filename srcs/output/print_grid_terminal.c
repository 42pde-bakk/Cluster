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

#define AB \
"          AAAAA                                                     BBBBB\n\
         A     A                                                    B    B\n\
         A     A                                                    BBBBBB\n\
         AAAAAAA                                                    B     B\n\
         A     A                                                    B    B\n\
         A     A                                                    BBBBB\n"

char *grid = 0;

void    print_grid_terminal(int opta, int optb)
{
	if (!grid)
		grid = generated_map(5);

    get_indices(get_opposite_direction(g_field.gravity));
    static const char	*items_double[6] = { WHT"  "RESET, WHT"{}"RESET, RED"##"RESET, YEL"@@"RESET, GRN"$$"RESET, BLU"&&"RESET };
    static const char	*items_A[6] = { WHT" "RESET, WHT"A"RESET, RED"#"RESET, YEL"@"RESET, GRN"$"RESET, BLU"&"RESET };
    static const char	*items_B[6] = { WHT" "RESET, WHT"B"RESET, RED"#"RESET, YEL"@"RESET, GRN"$"RESET, BLU"&"RESET };
    char    c;
    int     cell_idx = 0;
	int		iter = 0;

    system("clear");

    while (true)
    {
		c = grid[iter++];
        if (c == '.' || c == '\0')
            break;
        else if (c == '}')
            ;
        else if (c == '{')
        {
            printf("%s", items_double[tile_arr[tile_order[cell_idx]]->tile_colour + 1]);
            cell_idx++;
        }
        else if (c == '|' || c == 'v')
            printf(GRY "%c", c);
        else if (c == 'A') 
            printf("%s", items_A[opta + 1]);
        else if (c == 'B')
            printf("%s", items_B[optb + 1]);
        else
            printf(WHT "%c", c);
    }
	i = 0;
    printf("\n %d %d\n", opta, optb);
	while (AB[i])
	{
        if (AB[i] == 'A') {
            printf("%s", items_A[opta]);
        }
        else if (AB[i] == 'B') {
            printf("%s", items_B[optb]);
        }
		else
			printf("%c", AB[i]);
		i++;
	}
    printf("\n");
}
