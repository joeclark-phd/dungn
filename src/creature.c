#include "game.h"

Game* game;

bool attempt_move(Creature* c, int dy, int dx) {
    update_message_log_index();
    int newy = c->y + dy;
    int newx = c->x + dx;
    // check if walkable tile
    Tile** map = game->level->map;
    if(map[newy][newx].walkable) {
        c->y = newy;
        c->x = newx;
        add_message("player moved");
        return true;
    }
    // move failed
    add_message("can't move there");
    return false;
}
