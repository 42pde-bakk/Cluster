#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int width, height;

void edit_buf(int x, int y, char *data, char *str)
{
	int i = 0;
	while (str[i])
	{
		data[y * width + x] = str[i];
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
	for (size_t y = 0; y < height; y++)
	{
		if (data[y * width + x] == '_')
		{
			if (data[(y + 2) * width + x] == '{')
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
	for (size_t x = 0; x < width; x++)
	{
		if (is_center_node(data, x))
		{
			sprintf(num, "%d", i);
			i++;
			// padding missing but who cares
			edit_buf(x - 1, 0, data, num);
			for (size_t y = 1; y < height; y++)
			{
				if (data[(y + 1) * width + x] == '_')
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

char *generated_map(int len)
{
	int count = len * 2 - 1;
	int center = 7 + ((len - 1) * 8);

	width = ((len) * 16) - 4;
	height = (count * 4) + 5;
	printf("WIDTH %d %d\n", width, height);
	char *data = calloc((width * height) + 2, 1);
	if (data == 0)
		printf("ERROR\n");
	data[width * height] = 0;

	memset(data, ' ', (width * height));
	for (int i = 1; i < height; i++)
	{
		printf("%d\n", i);
		data[i * width - 1] = '$';
		data[i * width] = '\n';
	}

	int startDeclineEven = -1, startDeclineOdd  = -1;
	int curXEven = 0, curXOdd = 0;
	int inclineEven = 1, inclineOdd = 1;

	int y = 0;
	for (; y < count * 2; y += 1)
	{
		int x = 0, endX;

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

		// render
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
	data[(y * 2 + 5) * width] = '\0';
	add_arrows(data);
	return (data);
}

int main(int argc, char **argv)
{
	char *data = generated_map(atoi(argv[1]));
	printf("%s\n", data);
	free(data);
}
