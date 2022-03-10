#include "MLX42/MLX42.h"
#include "cluster.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "mlx.h"

int colors[6] = {0x000000ff, 0xffffffff, 0xff0000ff, 0xffff00ff, 0x00ff00ff, 0x00ffffff};
// black 0x0000ff
mlx_image_t	*g_img;
mlx_t	*g_mlx = NULL;

// void	hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
// 		mlx_close_window(param);
// 	if (mlx_is_key_down(param, MLX_KEY_UP))
// 		g_img->instances[0].y -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_DOWN))
// 		g_img->instances[0].y += 5;
// 	if (mlx_is_key_down(param, MLX_KEY_LEFT))
// 		g_img->instances[0].x -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
// 		g_img->instances[0].x += 5;
// }

void swap (int *a, int* b)
{
	int save;

	save = *a;
	*a = *b;
	*b = save;
}

void draw_line(mlx_image_t* image, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
{
	if (y1 >= y2 && x1 >= x2)
	{
		swap (&x1, &x2);
		swap (&y1, &y2);
	}
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx > dy)
	{
		for (int x = x1; x < x2; x++)
		{
			int y = y1 + dy * (x - x1) / dx;
			mlx_put_pixel(image, x, y, color);
		}
	}
	else 
	{
		for (int y = y1; y < y2; y++)
		{
			int x = x1 + dx * (y - y1) / dy;
			mlx_put_pixel(image, x, y, color);
		}
	}
}

void	draw_square(mlx_image_t* g_img, int x1, int y1, int x2, int y2, unsigned int color)
{
	for (int j = y1; j <= y2; j++)
	{
		for (int i = x1; i <= x2; i++)
		{
			mlx_put_pixel(g_img, i, j, color);
		}
	}
}

void draw_hex(mlx_image_t* g_img, int x, int y, int radius, int index, unsigned int color)
{
	float lastx = 0;
	float lasty = 0;
	for (int a = 0; a <= 360; a += 60)
	{
		float angle = a * M_PI / 180;
		float pointx = x + cos(angle) * radius;
		float pointy = y + sin(angle) * radius;
		if (lastx != 0 && lasty != 0)
		{
			draw_line(g_img, lastx, lasty, pointx, pointy, color);
			draw_square(g_img, x - radius / 2, y - radius / 2, x + radius / 2, y + radius / 2, colors[tile_arr[tile_order[index]]->tile_colour + 1]);
		}
		lastx = pointx;
		lasty = pointy;
	}
}

// void draw_vertical_chain(mlx_image_t* g_img, int x, int y, int radius, int amount, unsigned int color)
// {
// 	int	i = 1;
// 	int h = sqrt(3) * radius;
// 	if (amount % 2 == 0)
// 	{
// 		while (i < amount)
// 		{
// 			draw_hex(g_img, x, y + h * i / 2, radius, color);
// 			draw_hex(g_img, x, y - h * i / 2, radius, color);
// 			i += 2;
// 		}
// 	}
// 	else 
// 	{
// 		draw_hex(g_img, x, y, radius, color);
// 		while (i < amount)
// 		{
// 			draw_hex(g_img, x, y + h / 2 + h * i / 2, radius, color);
// 			draw_hex(g_img, x, y - h / 2 - h * i / 2, radius, color);
// 			i += 2;
// 		}
// 	}
// }

void draw_horizontal_chain(mlx_image_t* g_img, int x, int y, int radius, int amount, int index, unsigned int color)
{
	int	i = 0;

	while (i < amount)
	{
		// use index to decide the color
		draw_hex(g_img, x - 1.5 * radius - 3 * radius * amount / 2 + 3 * radius * (i + 1), y, radius, index, color);
		i++;
		index++;
	}
}

// void draw_vertical_grid(mlx_image_t* g_img, int x, int y, int radius, int amount, unsigned int color)
// {
// 	int i = 1;
// 	draw_vertical_chain(g_img, WIDTH / 2, y, radius, amount * 2 - 1, color);
// 	while (i < amount)
// 	{
// 		draw_vertical_chain(g_img, WIDTH / 2 - radius * 1.5 * i, y, radius, amount * 2 - i - 1, color);
// 		draw_vertical_chain(g_img, WIDTH / 2 + radius * 1.5 * i, y, radius, amount * 2 - i - 1, color);
// 		i++;
// 	}
// }

void draw_horizontal_grid(mlx_image_t* g_img, int x, int y, int radius, int amount, unsigned int color)
{
	int index = 0;
	int h = sqrt(3) * radius;

	for (int i = 1; i < amount - 1; i++)
	{
		draw_horizontal_chain(g_img, x, y - h * (amount) + h * i / 2 + h / 2, radius, i, index, color);
		index += i;
	}
	for (int i = 0; i < amount; i++)
	{
		draw_horizontal_chain(g_img, x, y - h * (amount) / 2 + h * i, radius, amount - 1, index, color);
		draw_horizontal_chain(g_img, x, y - h * (amount) / 2 + h * i + h / 2, radius, amount, index, color);
		index += i;
	}
	for (int i = amount - 1; i; i--)
	{
		draw_horizontal_chain(g_img, x, y + h * (amount) - h * i / 2 - h / 2, radius, i, index, color);
		index += amount - i;
	}
}

void print_grid_mlx(int col1, int col2)
{
	printf("g_mlx, g_img : %p, %p\n", g_mlx, g_img);
	(void)col1;
	(void)col2;
//	if (g_img)
//		mlx_delete_image(g_mlx, g_img);
//	g_img = mlx_new_image(g_mlx, WIDTH, HEIGHT);
	memset(g_img->pixels, 0, g_img->width * g_img->height * sizeof(int));
	draw_horizontal_grid(g_img, 500, 500, WIDTH / 3.5 / g_gameinfo.size, g_gameinfo.size, 0xffffffff);
	mlx_image_to_window(g_mlx, g_img, 0, 0);
//	mlx_loop(g_mlx);
}

int	start_mlx() {
	g_mlx = mlx_init(WIDTH, HEIGHT, "cluster", true);
	printf("init: g_mlx=%p\n", (void*)g_mlx);
	if (!g_mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(g_mlx, WIDTH, HEIGHT);
	if (!g_img)
		exit(EXIT_FAILURE);
	return (0);
}

// int32_t	mlx_main(void)
// {
	
	
// 	//old method, deos not correspond with array order
// 	//draw_vertical_grid(g_img, 500, 500, 50, 5, 0x00f3a4);

// 	// this one is made in the same order as our terminal grid.
// 	int amount = g_gameinfo.size;
// 	int radius = WIDTH / amount / 4;
// 	draw_horizontal_grid(g_img, 500, 500, radius, amount, 0xffffffff);

// 	//mlx_image_to_window(mlx, g_img, 0, 0);
// 	//mlx_loop_hook(mlx, &hook, mlx);
// 		//mlx_loop(mlx);

// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
