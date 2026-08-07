#include "game.h"

void generate_map(Level* lvl);
void room_carve(Level* lvl, Room room);
bool room_overlapping(Level* lvl, int index, Room room);
void rectangle_carve(Level* lvl, int ay, int ax, int by, int bx);

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
    free(lvl->rooms);
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
    free(dungeon->levels);
    free(dungeon);
}




void generate_map(Level* lvl) {
    // 1. fill level with solid rock
    Tile wall_prototype = (Tile) { .symbol='#', .transparent=false, .walkable=false };
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            lvl->map[y][x] = wall_prototype;
        }
    }
    // 2. generate rooms array
    lvl->num_rooms = rand_between(DN_MIN_ROOMS, DN_MAX_ROOMS);
    lvl->rooms = calloc(lvl->num_rooms, sizeof(Room));
    for(int r=0; r<lvl->num_rooms; ++r) {
        Room room;
        int height, width, y, x;
        do {
            height = rand_between(DN_MIN_ROOMSIZE, DN_MAX_ROOMSIZE);
            width = rand_between(DN_MIN_ROOMSIZE, DN_MAX_ROOMSIZE);
            y = rand_between(1, DN_HEIGHT-height-1);
            x = rand_between(1, DN_WIDTH-width-1);
            room = (Room) { .top_left=(Pos){y,x}, .height=height, .width=width};
        } while(room_overlapping(lvl, r, room));
        lvl->rooms[r] = room;
        // 3. mine out rooms
        room_carve(lvl, lvl->rooms[r]);
    }
    // 4. mine corridors between rooms
    for(int r=1; r<lvl->num_rooms; ++r) {
        Pos start = lvl->rooms[r-1].top_left;
        Pos end = lvl->rooms[r].top_left;
        int ax, bx, ay, by;
        ax = (start.x < end.x) ? start.x : end.x;
        bx = (start.x >= end.x) ? start.x : end.x;
        ay = (start.y < end.y) ? start.y : end.y;
        by = (start.y >= end.y) ? start.y : end.y;
        rectangle_carve(lvl, start.y, ax, start.y, bx);
        rectangle_carve(lvl, ay, end.x, by, end.x);
    }
}

void room_carve(Level* lvl, Room room) {
    Tile floor_prototype = (Tile) { .symbol='.', .transparent=true, .walkable=true };
    for(int y=room.top_left.y; y<room.top_left.y+room.height; ++y) {
        for(int x=room.top_left.x; x<room.top_left.x+room.width; ++x) {
            lvl->map[y][x] = floor_prototype;
        }
    }
}

void rectangle_carve(Level* lvl, int ay, int ax, int by, int bx) {
    Tile floor_prototype = (Tile) { .symbol='.', .transparent=true, .walkable=true };
    for(int y=ay; y<=by; ++y) {
        for(int x=ax; x<=bx; ++x) {
            lvl->map[y][x] = floor_prototype;
        }
    }
}

bool room_overlapping(Level* lvl, int index, Room room) {
    for(int r=0; r<index; ++r) {
        if(!(
            room.top_left.y + room.height < lvl->rooms[r].top_left.y 
            || room.top_left.y > lvl->rooms[r].top_left.y + lvl->rooms[r].height
            || room.top_left.x + room.width < lvl->rooms[r].top_left.x
            || room.top_left.x > lvl->rooms[r].top_left.x + lvl->rooms[r].width
        )) { return true; }
    }
    return false;
}
