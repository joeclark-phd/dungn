#ifndef CREATURE_H
#define CREATURE_H

#define PLAYER_VIS_RANGE 3.5

typedef struct Creature Creature;
struct Creature {
    int y;
    int x;
    char symbol;
    ItemVector* inventory;
};

bool attempt_move(Creature* c, int dy, int dx);
bool pick_up_item(Creature* c);
void open_inventory(Creature* c);

#endif