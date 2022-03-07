//
// Created by Peer De bakker on 3/7/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
	while (true) {
		char*	line = NULL;
		size_t	bytes = 0;
		if (getline(&line, &bytes, stdin) == -1) {
			exit(1);
		}
		printf("given input = '%s'\n", line);
		free(line);
	}
}
