#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "creature.h"
#include "dungeon.h"
#include "draw.h"
#include "util.h"

typedef struct Game Game;
struct Game {
    Creature player;
    Level* level;
    int turn;
};

// constructor + destructor
Game* game_init(void);
void game_destroy(Game*);

// globals
extern Game* game;

#endif