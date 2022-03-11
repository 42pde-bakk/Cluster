//
// Created by Peer De bakker on 3/7/22.
//

#include "player.h"
#include "move.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cluster.h>
#include "colours.h"
#include <limits.h>
#include <unistd.h>
#include <signal.h>

static t_move parse_input(const char input, const int value) {
	static const char*	strs[] = {
		"ALPHA", "BETA", "ROTATE", "\0"
	};
	for (size_t i = 0; i < sizeof(strs) / 8; ++i) {
		if (input == strs[i][0])
			return (t_move) {
				.type = (e_movetype)i,
				.value = value
			};
	}
	return (error_move());
}

int	is_valid(char type, const int value) {
	if (type == '\0')
	{
		printf(_YELLOW);
		printf("Error: missing spacebar between arguments\n");
		printf(_WHITE);
		return 0;
	}
	if ((type == 'A' || type == 'B' || type == 'R') == 0)
	{
		printf(_YELLOW);
		printf("Error: '%c' not a valid action\n", type);
		printf(_WHITE);
		return 0;
	}
	if (type != 'R' && (value <= 0 || value >= g_gameinfo.size * 2))
	{
		printf(_YELLOW);
		printf("Error: '%d' not a valid row\n", value);
		printf(_WHITE);
		return 0;
	}
	else if (type == 'R' && (value <= 0 || value > 5))
	{
		printf(_YELLOW);
		printf("Error: '%d' not a valid rotation value [1-%d]\n", value, g_gameinfo.size);
		printf(_WHITE);
		return 0;
	}	
	return (1);
}

t_player *g_player = NULL;
void	sigalarm_handler(int dummy) {
	(void)dummy;
	dprintf(STDERR_FILENO, "Player %s timed out (TIME_OUT is %d ms, but %d ms for the first turn)!\n", g_player->name, TIME_OUT, TIME_OUT * 20);
	fclose(g_player->reader);
}

t_move player_request_input(t_player *player, int turn) {
	char	movetype = 0;
	char	*input_line = NULL;
	size_t	line_cap = 0;
	size_t	line_len;
	int		value;

	if (player->pid) {
		g_player = player;
		signal(SIGALRM, &sigalarm_handler);
		if (!turn) // only for the first turn
			ualarm(TIME_OUT * 1000 * 20, 0);
		else
			ualarm(TIME_OUT * 1000, 0);
	}
	do {
		line_len = getline(&input_line, &line_cap, player->reader);
		if (line_len == ULONG_MAX) {
			free(input_line);
			return (error_move());
		}
		if (line_len >= 4 && input_line[1] == ' ')
			movetype = (char)toupper(input_line[0]);
		value = (int)strtol(input_line + 2, NULL, 10);
	// 	free(line_len);
	} while (!is_valid(movetype, value));
	ualarm(0, 0);
	t_move	move = parse_input(movetype, value);
	return (move);
}
