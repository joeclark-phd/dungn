#ifndef CREATURE_H
#define CREATURE_H

typedef struct Creature Creature;
struct Creature {
    char symbol;
    char* name;
    Pos pos;
};


#endif