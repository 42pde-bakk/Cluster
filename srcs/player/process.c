//
// Created by Peer De bakker on 3/7/22.
//

#include "player.h"

static void	fatal(const char* perror_msg) {
	perror(perror_msg);
	exit(EXIT_FAILURE);
}

static void	init_pipes(t_player *player) {
	if (pipe(player->stdin))
		fatal("pipe (STDIN): ");
	if (pipe(player->stdout))
		fatal("pipe (STDOUT): ");
}

void	child_close_pipes(t_player *player) {
	// Child process stdin/stdout  1/0 must be closed
	// the pipes becomes the stdin/stdout of the child process
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(player->stdin[STDOUT_FILENO]);//IN SO CLOSE OUT
	close(player->stdout[STDIN_FILENO]);//OUT SO CLOSE IN
}

int init_player_process(const char* path, t_player* player) {
	pid_t	pid;

	assert(player != NULL);
	init_pipes(player);
	if ((pid = fork()) == -1)
		fatal("fork:");

	if (pid == 0) {
//		int	ret;
//		child_close_pipes(player);

//		ret = dup2(player->stdin[STDIN_FILENO], STDIN_FILENO);
//		if (ret == -1)
//			fatal("dup2 (STDIN):");
//		ret = dup2(player->stdout[STDOUT_FILENO], STDOUT_FILENO);
//		if (ret == -1 || ret != STDOUT_FILENO)
//			fatal("dup2 (STDOUT): ");
		if (execve(path, NULL, NULL) == -1)
			fatal("execve:");
	}
	else {
		//Parent process save pids of the children
		printf("Player %s pid: %d\n", path, pid);
		player->pid = pid;
		//Close the pipes
		close(player->stdin[STDIN_FILENO]); //IN FOR PLAYER SO CLOSE IN
		close(player->stdout[STDOUT_FILENO]);
		player->reader = fdopen(player->stdout[STDIN_FILENO], "r");
		if (player->reader == NULL)
			fatal("fdopen:");
	}
	return (0);
}
