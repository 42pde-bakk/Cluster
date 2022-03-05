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

void    print_grid_terminal(char col1, char col2)
{
    FILE *grid = fopen("maps/grid5.txt", "r");
    get_indices(get_opposite_direction(g_field.gravity));
    char	*items[5] = { WHT"{}"RESET, BLU"##"RESET, RED"@@"RESET, GRN"$$"RESET, YEL"&&"RESET };
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
        else if (c == 'A')
        {
            if (col1 == 'r')
                printf(RED "%c", c);
            else if (col1 == 'y')
                printf(YEL "%c", c);
            else if (col1 == 'g')
                printf(GRN "%c", c);
            else if (col1 == 'b')
                printf(BLU "%c", c);
            else
                printf(WHT "%c", c);
        }
        else if (c == 'B')
        {
            if (col2 == 'r')
                printf(RED "%c", c);
            else if (col2 == 'y')
                printf(YEL "%c", c);
            else if (col2 == 'g')
                printf(GRN "%c", c);
            else if (col2 == 'b')
                printf(BLU "%c", c);
            else
                printf(WHT "%c", c);
        }
        else
            printf(WHT "%c", c);
    }
}

// void    print_grid_terminal(char col1, char col2)
// {
// 	//printf("in here!\n");
// 	char	*items[4] = { CYN"##"RESET, RED"@@"RESET, GRN"$$"RESET, YEL"&&"RESET };
// //	char	items[4] = {'#', '@', '$', '&'};
// //    FILE *grid = fopen("grid5.txt", "r");
//     int fd = open("../output/grid5.txt", O_RDONLY);
//     printf("fd = %d\n",fd);
//     if (fd == -1)
// 		return;

//     char buff[100000];

//     int ret = read(fd, buff, sizeof(buff));
// 	(void)ret;
// 	printf("ret = %d\n", ret);
//     printf(buff, items[tile_arr[60]->tile_colour]);
//     return ;
// //    char c;
    
// //    while (1)
// //    {
// //        c = getc(grid);
// //        if (c == '.')
// //            break;
// //        if (c == '{' || c == '}')
// //            printf(RED "%c", c);
// //        else if (c == '|' || c == 'v')
// //            printf(GRY "%c", c);
// //        else if (c == 'A')
// //        {
// //            if (col1 == 'r')
// //                printf(RED "%c", c);
// //            else if (col1 == 'y')
// //                printf(YEL "%c", c);
// //            else if (col1 == 'g')
// //                printf(GRN "%c", c);
// //            else if (col1 == 'b')
// //                printf(BLU "%c", c);
// //            else
// //                printf(WHT "%c", c);
// //        }
// //        else if (c == 'B')
// //        {
// //            if (col2 == 'r')
// //                printf(RED "%c", c);
// //            else if (col2 == 'y')
// //                printf(YEL "%c", c);
// //            else if (col2 == 'g')
// //                printf(GRN "%c", c);
// //            else if (col2 == 'b')
// //                printf(BLU "%c", c);
// //            else
// //                printf(WHT "%c", c);
// //        }
// //        else
// //            printf(WHT "%c", c);
// //    }
// }

//int main(void)
//{
//    print_grid_terminal('g', 'b');
//    printf("\n");
//    return (1);
//}
