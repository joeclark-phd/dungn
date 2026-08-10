#include "game.h"

int rand_between(int low, int high) {
    return low + (rand() % (1 + high - low));
}


Pos random_position_in_room(Room* r) {
    int y = rand_between(r->y, r->y+r->height-1);
    int x = rand_between(r->x, r->x+r->width-1);
    return (Pos) {y,x};
}