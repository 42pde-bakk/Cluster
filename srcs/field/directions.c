//
// Created by Peer De bakker on 3/5/22.
//

int	get_previous_direction(const int dir) {
	int previous_direction = dir - 1;
	if (previous_direction < 0)
		previous_direction = 6 + previous_direction;
	return (previous_direction);
}

int get_next_direction(const int dir) {
	return ((dir + 1) % 6);
}

int get_opposite_direction(const int dir) {
	return (dir + 3) % 6;
}

int get_link_direction(const int dir) {
	int link_dir = dir - 2;
	if (link_dir < 0)
		link_dir = 6 + link_dir;
	return (link_dir);
}
