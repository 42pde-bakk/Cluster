//
// Created by Peer De bakker on 3/7/22.
//

#include "player.h"
#include "move.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static t_move parse_input(const char* input_str, const int value) {
	static const char*	strs[] = {
			"ALPHA", "BETA", "ROTATE", "\0"
	};
	for (size_t i = 0; i < sizeof(strs); ++i) {
		if (strncmp(input_str, strs[i], 1) == 0)
			return (t_move) {
				.type = (e_movetype)i,
				.value = value
			};
	}
	return (error_move());
}

int	is_valid(char* type, const int value) {
	type[0] = toupper(type[0]);
	return ((type[0] == 'A' || type[0] == 'B' || type[0] == 'R') && type[1] == 0 && (0 < value && value < 9));
}

t_move	player_request_input(t_player *player) {
	char	movetype[100] = {0};
	char	movevalue[100] = {0};
	char	*input_line = NULL;
	size_t	line_cap = 0;
	size_t	line_len = 0;
	int		value = 0;

	(void)player;
	while (!is_valid(movetype, value)) {
		line_len = getline(&input_line, &line_cap, player->reader);
		printf("%zu\n", line_len);
		if (line_len == 4 && input_line[1] == ' ')
		{
			movetype[0] = input_line[0];
			movevalue[0] = input_line[2];
		}
		dprintf(2, "movetype='%s', movevalue='%s'\n", movetype, movevalue);
		value = (int)strtol(movevalue, NULL, 10);
	}
	t_move	move = parse_input(movetype, value);
	print_move(STDERR_FILENO, &move);
	return (move);
}
