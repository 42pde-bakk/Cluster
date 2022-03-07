//
// Created by Peer De bakker on 3/7/22.
//

#include "move.h"
#include <stdio.h>

t_move	error_move() {
	return ((t_move) {
			.type = ERROR,
			.value = -1
	});
}

void	print_move(int fd, const t_move *move) {
	static const char* strs[] = {
			"ROTATE", "DROP", "ERROR"
	};
	dprintf(fd, "move: %s [%d]\n", strs[move->type], move->value);
}
