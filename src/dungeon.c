#include "game.h"

void generate_map(Level* lvl);

Level* level_init(int depth) {
    Level* level = calloc(1, sizeof(Level));
    level->depth = depth;
    level->map = calloc(DN_HEIGHT, sizeof(Tile*));
    for(int i=0; i<DN_HEIGHT; ++i) {
        level->map[i] = calloc(DN_WIDTH, sizeof(Tile));
    }
    generate_map(level);
    return level;
}
void level_destroy(Level* lvl) {
    for(int i=0; i<DN_HEIGHT; ++i) {
        free(lvl->map[i]);
    }
    free(lvl->map);
    free(lvl);
}

Dungeon* dungeon_init(void) {
    Dungeon* dungeon = calloc(1, sizeof(Dungeon));
    dungeon->levels = calloc(DN_DEPTH, sizeof(Level*));
    dungeon->levels[0] = level_init(0);
    return dungeon;
};

void dungeon_destroy(Dungeon* dungeon) {
    for(int i=0; i<DN_DEPTH; ++i) {
        if(dungeon->levels[i]) {
            level_destroy(dungeon->levels[i]);
        }
    }
    free(dungeon);
}




void generate_map(Level* lvl) {
    // fill level with solid rock
    Tile wall_prototype = (Tile) { .symbol='#', .transparent=false, .walkable=false };
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            lvl->map[y][x] = wall_prototype;
        }
    }
    // carve out a room
    Tile floor_prototype = (Tile) { .symbol='.', .transparent=true, .walkable=true };
    for(int y=7; y<14; ++y) {
        for(int x=30; x<50; ++x) {
            lvl->map[y][x] = floor_prototype;
        }
    }
}