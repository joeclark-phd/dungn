#ifndef DUNGEON_H
#define DUNGEON_H

#define DN_DEPTH 5
#define DN_HEIGHT 21
#define DN_WIDTH 80

#define DN_MIN_ROOMS 6
#define DN_MAX_ROOMS 10

#define DN_MIN_ROOMSIZE 4
#define DN_MAX_ROOMSIZE 12

typedef struct Tile Tile;
struct Tile {
    char symbol;
    bool walkable;
    bool transparent;
};

typedef struct Room Room;
struct Room {
    Pos top_left;
    int height;
    int width;
};

typedef struct Level Level;
struct Level {
    int depth;
    Tile** map;
    int num_rooms;
    Room* rooms;
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