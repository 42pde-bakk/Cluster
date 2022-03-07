//
// Created by Peer De bakker on 3/7/22.
//

#include "player.h"
#include "move.h"
#include <string.h>
#include <ctype.h>
#include "colours.h"

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

int	is_valid(const char type, const int value) {
	if ((type == 'A' || type == 'B' || type == 'R') == 0)
	{
		printf(_YELLOW);
		printf("Error: '%c' not a valid character\n", type);
		printf(_WHITE);
		return 0;
	}
	if ((value <= 0 || value >= 10))
	{
		printf(_YELLOW);
		printf("Error: '%d' not a valid row\n", value);
		printf(_WHITE);
		return 0;
	}
	return (1);
}

t_move	player_request_input(t_player *player) {
	char	movechar = 0;
	char	movebuf[1024] = {0};
	int		value = 0;

	(void)player;
	do
	{
		if (fscanf(player->reader, "%s %d", movebuf, &value) == -1)
			continue;
		movechar = toupper(movebuf[0]);
	} while (!is_valid(movechar, value));

	t_move	move = parse_input(movechar, value);
	print_move(STDERR_FILENO, &move);
	return (move);
}
