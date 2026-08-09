#ifndef DUNGEON_H
#define DUNGEON_H

#define DN_HEIGHT 21
#define DN_WIDTH 80

typedef struct Tile Tile;
struct Tile {
    char symbol;
    bool walkable;
    bool transparent;
};

typedef struct Level Level;
struct Level {
    Tile** map;
    // monsters, items, etc
};


Level* level_init(void);
void level_destroy(Level*);

#endif