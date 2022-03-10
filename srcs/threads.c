//
// Created by Peer De bakker on 3/10/22.
//

#include "threads.h"
#include "cluster.h"
#include "mlx.h"

pthread_mutex_t	mutex_state;
pthread_mutex_t mutex_draw;
pthread_mutex_t	mutex_read;

pthread_t		thread_draw;

int				game_alive;
t_drawinfo		g_drawinfo;

static bool	alive_check() {
	bool alive;
	pthread_mutex_lock(&mutex_state);
	alive = game_alive;
	pthread_mutex_unlock(&mutex_state);
	return (alive);
}

void	*draw_loop(void *param) {
	size_t	i = 0;
//	mlx_t	*mlx = (mlx_t*)param;

	printf("in MEGA draw_loop\n");
	printf("started mlx, g_mlx = %p\n", g_mlx);

	(void)param;
	(void)i;
	while (alive_check()) {
		pthread_mutex_lock(&mutex_draw);
//		dprintf(STDERR_FILENO, "%zu. in draw_loop\n", i);
		if (g_drawinfo.can_draw) {
			print_grid_terminal(g_drawinfo.col1, g_drawinfo.col2, g_drawinfo.player);
			print_grid_mlx(g_drawinfo.col1, g_drawinfo.col2);
			g_drawinfo.can_draw = false;
		}
		pthread_mutex_unlock(&mutex_draw);
		usleep(5000);
	}
	printf("draw_loop died\n");
	return (NULL);
}

void	signal_print(int col1, int col2, const t_player *player) {
	printf("in signal_print\n");
	pthread_mutex_lock(&mutex_draw);
	g_drawinfo = (t_drawinfo) {
		.can_draw = true,
		.col1 = col1,
		.col2 = col2,
		.player = player
	};
	pthread_mutex_unlock(&mutex_draw);
	printf("out signal_print\n");
}

int	setup_threads() {
	game_alive = true;

	if (pthread_mutex_init(&mutex_draw, NULL) || pthread_mutex_init(&mutex_read, NULL) || pthread_mutex_init(&mutex_state, NULL))
		return (1);

	if (pthread_create(&thread_draw, NULL, draw_loop, NULL))
		return (1);
	dprintf(2, "initting mutexes and creating thread worked fine!\n");
	return (0);
}

int	thread_exit() {
	pthread_mutex_lock(&mutex_state);
	game_alive = false;
	pthread_mutex_unlock(&mutex_state);

	pthread_join(thread_draw, NULL);
	pthread_mutex_destroy(&mutex_state);
	pthread_mutex_destroy(&mutex_read);
	pthread_mutex_destroy(&mutex_draw);
	dprintf(2, "Destroyed all mutexes!\n");
	return (0);
}
