#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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

int is_center_node(char *data, int x)
{
	for (size_t y = 0; y < 100; y++)
	{
		if (data[y * 100 + x] == '_')
		{
			if (data[y * 100 + 200 + x] == '{')
				return (1);
			return (0);
		} 
	}
	return (0);
}

void add_arrows(char *data)
{
	int i = 1;
	char num[10];
	for (size_t x = 0; x < 100; x++)
	{
		if (is_center_node(data, x))
		{
			sprintf(num, "%d", i);
			i++;
			// padding missing but who cares
			edit_buf(x, 0, data, num);
			for (size_t y = 1; y < 100; y++)
			{
				if (data[(y + 1) * 100 + x] == '_')
				{
					edit_buf(x, y, data, "v");
					break;
				}
				else
					edit_buf(x, y, data, "|");
			}
			
		}
		
	}
		
}

char *generated(int len)
{
	int count = len * 2 - 1;
	static char data[10001];
	data[10000] = 0;

	memset(data, ' ', 10000);
	for (int i = 0; i < 100; i++)
	{
		data[i * 100] = '\n';
	}

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

		// boundries check
		if (y % 2 == 0)
		{
			curXEven += inclineEven;
			endX = curXEven;
			if (curXEven * 4 + 1 > count)
			{
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

		// print
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
			put_hex(center - xPos, (y * 2) + 5, data);
			put_hex(center + xPos, (y * 2) + 5, data);
		}
	}
	data[(y * 2 + 5) * 100] = '\0';
	add_arrows(data);
	printf("%s\n", data);
	return (data);
}

int main(int argc, char **argv)
{
	generated(atoi(argv[1]));
}