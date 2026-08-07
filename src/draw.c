#include "game.h"

Game* game;

void draw_map(void) {

    Tile** map = game->dungeon->levels[game->dungeon_level]->map;
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            mvaddch(y, x, map[y][x].symbol);
        }
    }

}
