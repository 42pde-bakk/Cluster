//
// Created by Peer De bakker on 3/5/22.
//

int get_opposite_direction(const int dir) {
	return (dir + 3) % 6;
}

int get_link_direction(const int dir) {
	int link_dir = dir - 2;
	if (link_dir < 0)
		link_dir = 6 + link_dir;
	return (link_dir);
}

int	direction_add(const int dir, const int add) {
	int new_dir = dir + add;
	while (new_dir < 0)
		new_dir = 6 + new_dir;
	return (new_dir % 6);
}

int	get_previous_direction(const int dir) {
	return (direction_add(dir, -1));
}

int get_next_direction(const int dir) {
	return (direction_add(dir, 1));
}
