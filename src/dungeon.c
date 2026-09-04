#include "game.h"

void generate_map(Level* lvl);
void mine_rectangle(Level* lvl, int starty, int startx, int endy, int endx);
Room random_room(Level* lvl);
bool overlaps_existing_room(Level* lvl, Room r);
void mine_corridor(Level* lvl, Room a, Room b);
void place_items(Level* lvl);


Level* level_init(void) {
    Level* level = calloc(1, sizeof(Level));
    level->map = calloc(DN_HEIGHT, sizeof(Tile*));
    for(int i=0; i<DN_HEIGHT; ++i) {
        level->map[i] = calloc(DN_WIDTH, sizeof(Tile));
    }
    level->rooms = calloc(DN_ROOMS_PER_LEVEL, sizeof(Room));
    level->num_rooms = 0;
    generate_map(level);
    place_items(level);
    return level;
}





void generate_map(Level* lvl) {
    // fill level with solid rock
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            lvl->map[y][x].symbol = '#';
            lvl->map[y][x].walkable = false;
            lvl->map[y][x].transparent = false;
            lvl->map[y][x].remembered = false;
        }
    }
    // make random rooms
    for(int r=0; r<DN_ROOMS_PER_LEVEL; ++r) {
        Room rm = random_room(lvl);
        lvl->rooms[r] = rm;
        lvl->num_rooms += 1;
        mine_rectangle(lvl, rm.y, rm.x, rm.y+rm.height-1, rm.x+rm.width-1);
        if(r>0) {
            mine_corridor(lvl, lvl->rooms[r-1], lvl->rooms[r]);
        }
    }
}





void mine_rectangle(Level* lvl, int starty, int startx, int endy, int endx) {
    for(int y=starty; y<=endy; ++y) {
        for(int x=startx; x<=endx; ++x) {
            lvl->map[y][x].symbol = '.';
            lvl->map[y][x].walkable = true;
            lvl->map[y][x].transparent = true;
            lvl->map[y][x].remembered = false;
        }
    }
}

Room random_room(Level* level) {
    Room r;
    do{
        r.height = rand_between(4,12);
        r.width = rand_between(4,12);
        r.y = rand_between(1, DN_HEIGHT-1-r.height);
        r.x = rand_between(1, DN_WIDTH-1-r.width);
    } while(overlaps_existing_room(level, r));
    return r;
}

bool overlaps_existing_room(Level* lvl, Room r) {
    for(int i=0; i<lvl->num_rooms; ++i) {
        Room e = lvl->rooms[i];
        if(!(
            r.y+r.height < e.y // entirely above
            || r.y > e.y+e.height // entirely below
            || r.x+r.width < e.x // to the left
            || r.x > e.x+e.width // to the right
        )) {
            return true;
        }
    }
    return false;
}


void mine_corridor(Level* lvl, Room a, Room b) {
    int y = rand_between(a.y, a.y+a.height-1);
    int x = rand_between(a.x, a.x+a.width-1);
    int by = rand_between(b.y, b.y+b.height-1);
    int bx = rand_between(b.x, b.x+b.width-1);

    Tile prototype = (Tile) {
        .symbol='.',
        .transparent=true,
        .walkable=true,
        .remembered=false
    };
    while(x != bx) {
        // make tile to floor
        lvl->map[y][x] = prototype;
        // update x closer to bx
        x = (x<bx) ? x + 1 : x - 1;
    }
    while(y != by) {
        // make tile to floor
        lvl->map[y][x] = prototype;
        // update y closer to by
        y = (y<by) ? y + 1 : y - 1;
    }
}



void level_destroy(Level* level) {
    for(int i=0; i<DN_HEIGHT; ++i) {
        free(level->map[i]);
    }
    free(level->map);
    free(level->rooms);
    free(level);
}

void place_items(Level* lvl) {
    for(int i=0; i<DN_ITEMS_PER_LEVEL; ++i) {
        // pick a random room
        Room* rm = random_room_in_level(lvl);
        // pick a random location
        Pos loc = random_position_in_room(rm);
        // place the item
        Item i = ITEMCATALOG[rand_between(0,5)];
        Tile* t = &lvl->map[loc.y][loc.x];
        if(!t->items) {
            t->items = item_vector_create();
        }
        item_add(t->items, i);
    }
}
