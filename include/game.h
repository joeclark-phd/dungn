#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include "creature.h"
#include "dungeon.h"
#include "draw.h"

typedef struct Game Game;
struct Game {
    Creature player;
    Level* level;
};

// constructor + destructor
Game* game_init(void);
void game_destroy(Game*);

// globals
extern Game* game;

#endif