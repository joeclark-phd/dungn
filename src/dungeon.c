#include "game.h"

void generate_map(Level* lvl);
void mine_rectangle(Level* lvl, int starty, int startx, int endy, int endx);
Room random_room(void);

Level* level_init(void) {
    Level* level = calloc(1, sizeof(Level));
    level->map = calloc(DN_HEIGHT, sizeof(Tile*));
    for(int i=0; i<DN_HEIGHT; ++i) {
        level->map[i] = calloc(DN_WIDTH, sizeof(Tile));
    }
    level->rooms = calloc(DN_ROOMS_PER_LEVEL, sizeof(Room));
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
    for(int r=0; r<DN_ROOMS_PER_LEVEL; ++r) {
        Room rm = random_room();
        lvl->rooms[r] = rm;
        mine_rectangle(lvl, rm.y, rm.x, rm.y+rm.height-1, rm.x+rm.width-1);
    }
}

void mine_rectangle(Level* lvl, int starty, int startx, int endy, int endx) {
    for(int y=starty; y<=endy; ++y) {
        for(int x=startx; x<=endx; ++x) {
            lvl->map[y][x].symbol = '.';
            lvl->map[y][x].walkable = true;
            lvl->map[y][x].transparent = true;
        }
    }
}

Room random_room(void) {
    Room r;
    r.height = rand_between(4,12);
    r.width = rand_between(4,12);
    r.y = rand_between(1, DN_HEIGHT-1-r.height);
    r.x = rand_between(1, DN_WIDTH-1-r.width);
    return r;
}

void level_destroy(Level* level) {
    for(int i=0; i<DN_HEIGHT; ++i) {
        free(level->map[i]);
    }
    free(level->map);
    free(level->rooms);
    free(level);
}

