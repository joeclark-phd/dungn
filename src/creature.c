#include "game.h"

Game* game;

bool attempt_move(Creature* c, int dy, int dx) {
    int newy = c->y + dy;
    int newx = c->x + dx;
    // check if walkable tile
    Tile** map = game->level->map;
    if(map[newy][newx].walkable) {
        c->y = newy;
        c->x = newx;
        return true;
    }
    // move failed
    return false;
}
