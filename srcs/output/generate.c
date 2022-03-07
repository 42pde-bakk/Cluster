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

char *generated(int count)
{
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
	int center = 50;
	int startDeclineEven = -1, startDeclineOdd  = -1;
	float maxEven = floor(count / 4);
	float maxOdd = floor(count / 4);
	int curXEven = 0, curXOdd = 0;
	int inclineEven = 1, inclineOdd = 1;

	printf("MAX: %f, %f\n", maxEven, maxOdd);

	for (size_t y = 0; y < count * 2; y += 1)
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
				inclineEven = 0;
				if (startDeclineEven == -1)
					startDeclineEven = count * 2 - y;
				// inclineOdd = 0;
				// if (startDeclineOdd == -1)
				// 	startDeclineOdd = count * 2 - y;
			}
		}
		else
		{
			curXOdd += inclineOdd;
			endX = curXOdd;
			if (((curXOdd + 1) * 4) - 1 > count)
			{
				inclineOdd = 0;
				if (startDeclineOdd == -1)
					startDeclineOdd = count * 2 - y;
			}
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
			printf("XPOS %d %d %d %d\n",y, xPos, curXEven, inclineEven);
			// if (x / 2 < endX / 2)
			// 	xPos = center - xPos;
			// else
			// 	xPos = center + xPos;
			put_hex(center - xPos, (y * 2) + 10, data);
			put_hex(center + xPos, (y * 2) + 10, data);

		}
	}
	
	

	printf("$%s\n", data);
}

int main(int argc, char **argv)
{
	generated(atoi(argv[1]));
}