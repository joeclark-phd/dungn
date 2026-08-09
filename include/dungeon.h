#ifndef DUNGEON_H
#define DUNGEON_H

#define DN_HEIGHT 21
#define DN_WIDTH 80
#define DN_ROOMS_PER_LEVEL 12

typedef struct Tile Tile;
struct Tile {
    char symbol;
    bool walkable;
    bool transparent;
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
    // monsters, items, etc
};


Level* level_init(void);
void level_destroy(Level*);

#endif