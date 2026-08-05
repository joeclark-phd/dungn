#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>

#include "util.h"
#include "creature.h"

typedef struct Game Game;
struct Game {
    Creature player;
    int turn;
    int dungeon_level;
    // Dungeon dungeon;
};

Game* game_init(void);
void game_destroy(Game*);

// global variable
extern Game* game;

#endif