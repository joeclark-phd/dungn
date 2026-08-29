#include "game.h"

Game* game;

bool attempt_move(Creature* c, int dy, int dx) {
    flush_message_log();
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
    add_message("You bumped into a wall.");
    return false;
}
