#ifndef ITEM_H
#define ITEM_H

#define ITEM_MAX_IN_VECTOR 21

typedef enum item_type item_type;
enum item_type { WEAPON, ARMOR, NON_EQUIPPABLE };

typedef struct Item Item;
struct Item {
    char symbol;
    char* name;
    short color;
    item_type type;
    int power;
    bool equipped;
};

#define LONGSWORD (Item) {'/', "longsword", CP_GRAY, WEAPON, 8, false}
#define HAND_AXE (Item) {'/', "hand axe", CP_RED, WEAPON, 6, false}
#define LEATHER_ARMOR (Item) {'(', "leather armor", CP_BROWN, ARMOR, 3, false}
#define CHAIN_MAIL (Item) {'[', "chain mail", CP_GRAY, ARMOR, 5, false}
#define SCROLL_TELEPORT (Item) {'?', "scroll of teleport", CP_WHITE, NON_EQUIPPABLE, false}
#define POTION_HEALING (Item) {'!', "potion of healing", CP_PURPLE, NON_EQUIPPABLE, false}

#define ITEMCATALOG (Item[]) { LONGSWORD, HAND_AXE, \
    LEATHER_ARMOR, CHAIN_MAIL, SCROLL_TELEPORT,     \
    POTION_HEALING}

// a variable-length collection of items
typedef struct ItemVector ItemVector;
struct ItemVector {
    Item* items;
    int count;
};

//functions
ItemVector* item_vector_create(void);
void item_vector_destroy(ItemVector*);
bool item_add(ItemVector*, Item);
void item_remove(ItemVector*, int index);

#endif