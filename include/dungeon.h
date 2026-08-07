#ifndef DUNGEON_H
#define DUNGEON_H

#define DN_DEPTH 5
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
    int depth;
    Tile** map;
    // items, monsters, etc
};

typedef struct Dungeon Dungeon;
struct Dungeon {
    Level** levels;
};

// constructors/destructors
Level* level_init(int depth);
void level_destroy(Level*);
Dungeon* dungeon_init(void);
void dungeon_destroy(Dungeon*);



#endif