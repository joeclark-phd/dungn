#ifndef CREATURE_H
#define CREATURE_H

#define PLAYER_VIS_RANGE 3.5

typedef struct Creature Creature;
struct Creature {
    char symbol;
    char* name;
    short color;
    char* attack_verb;
    int y;
    int x;
    ItemVector* inventory;
};

#define MOUSE (Creature) { 'r', "mouse", CP_WHITE, "bites", 0, 0, 0 }
#define GOBLIN (Creature) { 'g', "goblin", CP_GREEN, "stabs", 0, 0, 0 }
#define SPIDER (Creature) { 'x', "cave spider", CP_BLUE, "stings", 0, 0, 0 }

#define CREATURE_CATALOG (Creature[]) { MOUSE, GOBLIN, SPIDER }

// a variable-length collection of items
typedef struct CreatureVector CreatureVector;
struct CreatureVector {
    Creature* creatures;
    int count;
};

bool attempt_move(Creature* c, int dy, int dx);
bool pick_up_item(Creature* c);
void open_inventory(Creature* c);

CreatureVector* creature_vector_create(void);
void creature_vector_destroy(CreatureVector*);
void creature_add(CreatureVector*, Creature);
void creature_remove(CreatureVector*, int index);

#endif