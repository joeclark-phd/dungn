#ifndef CREATURE_H
#define CREATURE_H

#define PLAYER_VIS_RANGE 2.5

typedef struct Creature Creature;
struct Creature {
    int y;
    int x;
    char symbol;
};

bool attempt_move(Creature* c, int dy, int dx);

#endif