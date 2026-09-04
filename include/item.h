#ifndef ITEM_H
#define ITEM_H

#define ITEM_MAX_IN_VECTOR 20

typedef struct Item Item;
struct Item {
    char symbol;
    char* name;
    short color;
};

#define LONGSWORD (Item) {'/', "longsword", CP_GRAY}
#define HAND_AXE (Item) {'/', "hand axe", CP_RED}
#define LEATHER_ARMOR (Item) {'(', "leather armor", CP_BROWN}
#define CHAIN_MAIL (Item) {'[', "chain mail", CP_GRAY}
#define SCROLL_TELEPORT (Item) {'?', "scroll of teleport", CP_WHITE}
#define POTION_HEALING (Item) {'!', "potion of healing", CP_PURPLE}

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