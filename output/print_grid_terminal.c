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
    //printf("hi\n");
    FILE *grid = fopen("../output/grid5.txt", "r");
    int     tile_order[64] = {37, 60, 38, 59, 19, 39, 58, 36, 20, 40, 57, 35, 7, 21, 41, 34, 18, 8, 22, 56, 17, 1, 9, 42, 33, 6, 2, 23, 55, 16, 0, 10, 43, 32, 5, 3, 24, 54, 15, 4, 11, 44, 31, 14, 12, 25, 53, 30, 13, 26, 45, 52, 29, 27, 46, 51, 28, 47, 50, 48, 49};
    char	*items[5] = { WHT"{}"RESET, BLU"##"RESET, RED"@@"RESET, GRN"$$"RESET, YEL"&&"RESET };
    char    c;
    int     i = 0;
    
    while (1)
    {
        c = getc(grid);
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
    return ;
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
