#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct Pos Pos;
struct Pos {
    int y;
    int x;
};

#include "item.h"
#include "creature.h"
#include "dungeon.h"
#include "util.h"
#include "draw.h"



typedef struct Game Game;
struct Game {
    Creature player;
    Level** all_levels;
    int current_depth;
    Level* level;
    int turn;
    char** status_log;
    int last_status_index;
    int previous_last_status;
    int monsters_killed;
    int deepest_level_reached;
};

// constructor + destructor
Game* game_init(void);
void game_destroy(Game*);

// functions
void show_message_log(void);
void advance_message_log(void);
void flush_message_log(void);
void add_message(char* message);

void attempt_down_stairs(Creature* player);
void attempt_up_stairs(Creature* player);
void splash_screen(char* message);

// globals
extern Game* game;

#endif