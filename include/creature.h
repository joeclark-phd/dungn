#ifndef CREATURE_H
#define CREATURE_H

#define PLAYER_VIS_RANGE 3.5
#define MONSTER_VIS_RANGE 5.5

typedef struct Creature Creature;
struct Creature {
    char symbol;
    char* name;
    short color;
    char* attack_verb;
    int max_attack;
    int armorclass;
    int maxhp;
    int hp;
    int thac0;
    int y;
    int x;
    ItemVector* inventory;
};

#define MOUSE (Creature) { 'r', "mouse", CP_WHITE, "bites", 3, 4, 2, 2, 20, 0, 0, 0 }
#define GOBLIN (Creature) { 'g', "goblin", CP_GREEN, "stabs", 6, 10, 5, 5, 20, 0, 0, 0 }
#define SPIDER (Creature) { 'x', "cave spider", CP_BLUE, "stings", 4, 6, 4, 4, 20, 0, 0, 0 }

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

int monster_at(int y, int x);
void monsters_move();

#endif