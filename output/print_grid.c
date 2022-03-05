/* Created by jaberkro on march 5th 22. */

#include <stdio.h>
#include <unistd.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define GRY   "\x1B[90m"
#define RESET "\x1B[0m"


void    print_grid(char col1, char col2)
{
    FILE *grid = fopen("grid5.txt", "r");
    char c;
    
    while (1)
    {
        c = getc(grid);
        if (c == '.')
            break;
        if (c == '{' || c == '}')
            printf(RED "%c", c);
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

int main(void)
{
    print_grid('g', 'b');
    printf("\n");
    return (1);
}
