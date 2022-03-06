//
// Created by Peer De bakker on 3/6/22.
//

#include "cluster.h"
#include <assert.h>

void   rotate_field(int direction) {
    assert(direction > 0 && direction < 6);
    // if direction isn't within 1 and 5, this throws an error.
    g_field.gravity = (g_field.gravity + direction) % 6;

    printf("gravity now is %d\n", g_field.gravity);

    print_grid_terminal();

    // No need to update the corners
}
