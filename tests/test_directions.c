//
// Created by Peer De bakker on 3/5/22.
//
#include <stdio.h>
#include <assert.h>
#include "cluster.h"

int previous_direction() {
	assert(get_previous_direction(0) == 5);
	assert(get_previous_direction(1) == 0);
	assert(get_previous_direction(2) == 1);
	assert(get_previous_direction(3) == 2);
	assert(get_previous_direction(4) == 3);
	assert(get_previous_direction(5) == 4);
	return (0);
}

int next_direction() {
	assert(get_next_direction(0) == 1);
	assert(get_next_direction(1) == 2);
	assert(get_next_direction(2) == 3);
	assert(get_next_direction(3) == 4);
	assert(get_next_direction(4) == 5);
	assert(get_next_direction(5) == 0);
	return (0);
}

int	opposite_direction() {
	assert(get_opposite_direction(0) == 3);
	assert(get_opposite_direction(1) == 4);
	assert(get_opposite_direction(2) == 5);
	assert(get_opposite_direction(3) == 0);
	assert(get_opposite_direction(4) == 1);
	assert(get_opposite_direction(5) == 2);
	return (0);
}

int link_direction() {
	assert(get_link_direction(0) == 4);
	assert(get_link_direction(1) == 5);
	assert(get_link_direction(2) == 0);
	assert(get_link_direction(3) == 1);
	assert(get_link_direction(4) == 2);
	assert(get_link_direction(5) == 3);
	return (0);
}

int main() {
	previous_direction();
	next_direction();
	opposite_direction();
	link_direction();
	printf("tests succeeded!\n");
	return (0);
}
