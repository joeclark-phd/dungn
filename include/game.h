#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "creature.h"
#include "dungeon.h"
#include "draw.h"
#include "util.h"

typedef struct Game Game;
struct Game {
    Creature player;
    Level* level;
    int turn;
    char** status_log;
    int last_status_index;
    int previous_last_status;
};

// constructor + destructor
Game* game_init(void);
void game_destroy(Game*);

// functions
void show_message_log(void);
void update_message_log_index(void);
void advance_message_log(void);

// globals
extern Game* game;

#endif