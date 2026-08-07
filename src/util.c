#include "game.h"

int rand_between(int low, int high) {
    return low + (rand() % (high-low+1));
}