#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define SI_WIDTH 11
#define SI_HEIGHT 5

void edit_buf(int x, int y, char *data, char *str)
{
	int i = 0;
	while (str[i])
	{
		data[y * 100 + x] = str[i];
		i++;
		x++;
	}
}

void put_hex(int x, int y, char *data)
{
	edit_buf(x - 4, y - 2,	data, "______");
	edit_buf(x - 5, y - 1,	data, "/      \\");
	edit_buf(x - 6, y,		data, "/   {}   \\");
	edit_buf(x - 6, y + 1,	data, "\\        /");
	edit_buf(x - 5, y + 2,	data, "\\______/");
}

char *generated(int len)
{
	int count = len * 2 - 1;
	char data[10001];
	data[10000] = 0;

	memset(data, ' ', 10000);
	for (int i = 0; i < 100; i++)
	{
		data[i * 100] = '\n';
	}

	// 1: 7
	// 2:
	// int center = 7 + (count - 1) * 8;
	int center = 7 + ((len - 1) * 8);
	int startDeclineEven = -1, startDeclineOdd  = -1;
	int curXEven = 0, curXOdd = 0;
	int inclineEven = 1, inclineOdd = 1;

	size_t y = 0;
	for (; y < count * 2; y += 1)
	{
		size_t x = 0, endX;

		if (y == startDeclineEven)
			inclineEven = -1;
		if (y == startDeclineOdd)
			inclineOdd = -1;

		if (y % 2 == 0)
		{
			curXEven += inclineEven;
			endX = curXEven;
			if (curXEven * 4 + 1 > count)
			{
				printf("EVEN TRIGGER\n");
				inclineEven = 0;
				if (startDeclineEven == -1)
					startDeclineEven = count * 2 - y;
			}
		}
		else
		{
			if (inclineOdd == 1 && (curXOdd + 1) * 2 + ((curXOdd) * 2) > count)
			{
				inclineOdd = 0;
				if (startDeclineOdd == -1)
					startDeclineOdd = count * 2 - (y - 1);
			}
			curXOdd += inclineOdd;
			endX = curXOdd;
		}

		for (; x < endX; x++)
		{
			int xPos = 0;
			if (y % 2 == 0)
			{
				xPos = x * 16;
			}
			else
			{
				if (count == 1)
					break;
				xPos = 8 + x * 16;
			}
			printf("XPOS %d %d %d\n",y, xPos, curXEven, inclineEven);
			put_hex(center - xPos, (y * 2) + 2, data);
			put_hex(center + xPos, (y * 2) + 2, data);
		}
	}
	data[(y * 2 + 1) * 100] = '\0';
	printf("%s\n", data);
}

int main(int argc, char **argv)
{
	generated(atoi(argv[1]));
}