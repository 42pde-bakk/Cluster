//
// Created by Peer De bakker on 3/10/22.
//

#ifndef CLUSTER_MLX_H
# define CLUSTER_MLX_H

# define WIDTH 1000
# define HEIGHT 1000

# include "MLX42/MLX42.h"

void	print_grid_mlx(int col1, int col2);
int		start_mlx();

extern mlx_t	*g_mlx;


#endif //CLUSTER_MLX_H
