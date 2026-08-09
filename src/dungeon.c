#include "game.h"

void generate_map(Level* lvl);

Level* level_init(void) {
    Level* level = calloc(1, sizeof(Level));
    level->map = calloc(DN_HEIGHT, sizeof(Tile*));
    for(int i=0; i<DN_HEIGHT; ++i) {
        level->map[i] = calloc(DN_WIDTH, sizeof(Tile));
    }
    generate_map(level);
    return level;
}

void generate_map(Level* lvl) {
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            lvl->map[y][x].symbol = '#';
            lvl->map[y][x].walkable = false;
            lvl->map[y][x].transparent = false;
        }
    }
}





void level_destroy(Level* level) {
    for(int i=0; i<DN_HEIGHT; ++i) {
        free(level->map[i]);
    }
    free(level->map);
    free(level);
}

