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
    int xp; // for player, his XP. for monster, the XP value of killing one.
    int level;
    int y;
    int x;
    ItemVector* inventory;
    magic_type effect;
    int effect_duration;
};

// animal
#define MOUSE (Creature) { 'm', "mouse", CP_WHITE, "bites", 2, 4, 2, 2, 20, 200, 0, 0, 0, 0}
#define RACCOON (Creature) { 'r', "raccoon", CP_BROWN, "scratches", 5, 4, 4, 4, 20, 400, 0, 0, 0, 0}
#define COYOTE (Creature) { 'c', "coyote", CP_RED, "bites", 6, 6, 5, 5, 20, 800, 0, 0, 0, 0 }
#define BADGER (Creature) { 'b', "honey badger", CP_GOLD, "claws", 8, 6, 7, 7, 20, 1600, 0, 0, 0, 0}
#define BEAR (Creature) { 'B', "grizzly bear", CP_BROWN, "mauls", 10, 9, 10, 10, 20, 3200, 0, 0, 0, 0 }

// humanoid villain
#define KOBOLD (Creature) { 'k', "kobold", CP_BLUE, "hits", 6, 8, 5, 5, 20, 200, 0, 0, 0, 0 }
#define GOBLIN (Creature) { 'g', "goblin", CP_GREEN, "stabs", 7, 9, 7, 7, 20, 400, 0, 0, 0, 0 }
#define ORC (Creature) { 'o', "orc", CP_ORANGE, "slashes", 8, 10, 9, 9, 20, 800, 0, 0, 0, 0 }
#define HOBGOBLIN (Creature) { 'h', "hobgoblin", CP_PURPLE, "whacks", 9, 11, 11, 5, 20, 1600, 0, 0, 0 , 0}
#define OGRE (Creature) { 'O', "ogre", CP_CYAN, "smites", 10, 12, 13, 13, 20, 3200, 0, 0, 0, 0 }

// creepy crawly
#define SNAIL (Creature) { 's', "slime snail", CP_BLUE, "slimes", 4, 6, 2, 2, 20, 200, 0, 0, 0, 0 }
#define SPIDER (Creature) { 'x', "cave spider", CP_BLUE, "nibbles", 5, 6, 3, 3, 20, 400, 0, 0, 0 , 0}
#define SCORPION (Creature) { 'X', "scorpion", CP_BLUE, "stings", 6, 6, 4, 4, 20, 800, 0, 0, 0 , 0}
#define LIZARD (Creature) { 'l', "warty lizard", CP_BLUE, "bites", 7, 6, 5, 5, 20, 1600, 0, 0, 0 , 0}
#define SNAKE (Creature) { 'S', "big snake", CP_BLUE, "constricts", 8, 6, 6, 6, 20, 3200, 0, 0, 0, 0 }

#define CREATURE_CATALOG (Creature*[]) {        \
    (Creature[]) { MOUSE, KOBOLD, SNAIL },     \
    (Creature[]) { RACCOON, GOBLIN, SPIDER },     \
    (Creature[]) { COYOTE, ORC, SCORPION },     \
    (Creature[]) { BADGER, HOBGOBLIN, LIZARD },     \
    (Creature[]) { BEAR, OGRE, SNAKE },     \
}

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

int monster_at(CreatureVector* vec, int y, int x);
void monsters_move();

void add_xp(int xp);

#endif