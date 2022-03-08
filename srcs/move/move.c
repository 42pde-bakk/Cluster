//
// Created by Peer De bakker on 3/7/22.
//

#include "move.h"
#include <stdio.h>
#include "cluster.h"

typedef const t_tile*	(*t_jump)();

t_move	error_move() {
	return ((t_move) {
		.type = ERROR,
		.value = -1
	});
}

void	print_move(int fd, const t_move *move) {
	static const char* strs[] = {
		"DROP A", "DROP B", "ROTATE", "ERROR"
	};
	dprintf(fd, "move: %s [%d]\n", strs[move->type], move->value);
}

static const t_tile	*wrong_move(const t_move *move) {
	(void)move;
	dprintf(STDERR_FILENO, "WRONG MOVE\n");
	print_move(STDERR_FILENO, move);
	return (NULL);
}

const t_tile	*execute_move(const t_move *move) {
	static const t_jump	jumptable[] = {
		[ALPHA] = &get_drop_tile,
		[BETA] = &get_drop_tile,
		[ROTATE] = &rotate_field,
		[ERROR] = &wrong_move,
	};
	print_move(2, move);
	return (jumptable[move->type](move));
}
