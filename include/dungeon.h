#ifndef DUNGEON_H
#define DUNGEON_H

#define DN_HEIGHT 21
#define DN_WIDTH 80
#define DN_ROOMS_PER_LEVEL 8

typedef struct Tile Tile;
struct Tile {
    char symbol;
    bool walkable;
    bool transparent;
    bool visible;
};

typedef struct Room Room;
struct Room {
    int y;
    int x;
    int width;
    int height;
};

typedef struct Level Level;
struct Level {
    Tile** map;
    Room* rooms;
    int num_rooms;
    // monsters, items, etc
};


Level* level_init(void);
void level_destroy(Level*);

#endif