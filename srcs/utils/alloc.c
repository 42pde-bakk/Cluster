//
// Created by Peer De bakker on 3/8/22.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	fatal() {
	dprintf(STDERR_FILENO, "Error. Malloc failed\n");
	exit(EXIT_FAILURE);
}

void	*ft_malloc(size_t size) {
	void	*ptr = malloc(size);

	if (!ptr)
		fatal();
	return (ptr);
}

void	*ft_calloc(size_t count, size_t size) {
	void	*ptr = calloc(count, size);

	if (!ptr)
		fatal();
	return (ptr);
}
