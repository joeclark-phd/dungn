#ifndef ITEM_H
#define ITEM_H

#define ITEM_MAX_IN_VECTOR 21

typedef enum item_type item_type;
enum item_type { WEAPON, ARMOR, NON_EQUIPPABLE };
typedef enum magic_type magic_type;
enum magic_type { NONE, HEAL, TELEPORT, INVISIBILITY, STRENGTH, LIGHT, MAPPING };

typedef struct Item Item;
struct Item {
    char symbol;
    char* name;
    short color;
    item_type type;
    magic_type magic;
    int power;
    bool equipped;
};

#define DAGGER (Item) {'/', "dagger", CP_GRAY, WEAPON, NONE, 4, false}
#define HAND_AXE (Item) {'/', "hand axe", CP_RED, WEAPON, NONE, 5, false}
#define SPEAR (Item) {'/', "spear", CP_BROWN, WEAPON, NONE, 6, false}
#define SHORTSWORD (Item) {'/', "short sword", CP_GRAY, WEAPON, NONE, 8, false}
#define LONGSWORD (Item) {'/', "longsword", CP_GRAY, WEAPON, NONE, 10, false}

#define CLOAK (Item) {'(', "wool cloak", CP_WHITE, ARMOR, NONE, 2, false}
#define LEATHER_ARMOR (Item) {'(', "leather armor", CP_BROWN, ARMOR, NONE, 4, false}
#define RING_MAIL (Item) {'(', "ring mail", CP_GREEN, ARMOR, NONE, 6, false}
#define CHAIN_MAIL (Item) {'[', "chain mail", CP_GRAY, ARMOR, NONE, 8, false}
#define PLATE_MAIL (Item) {'[', "plate mail", CP_WHITE, ARMOR, NONE, 9, false}

#define SCROLL_TELEPORT (Item) {'?', "scroll of teleport", CP_WHITE, NON_EQUIPPABLE, TELEPORT, 0, false}
#define SCROLL_LIGHT (Item) {'?', "scroll of light", CP_WHITE, NON_EQUIPPABLE, LIGHT, 0, false}
#define SCROLL_MAPPING (Item) {'?', "scroll of magic mapping", CP_WHITE, NON_EQUIPPABLE, MAPPING, 0, false}
#define POTION_HEALING (Item) {'!', "potion of healing", CP_PURPLE, NON_EQUIPPABLE, HEAL, 0, false}
#define POTION_INVISIBILITY (Item) {'!', "potion of invisibility", CP_ORANGE, NON_EQUIPPABLE, INVISIBILITY, 0, false}
#define POTION_STRENGTH (Item) {'!', "potion of strength", CP_CYAN, NON_EQUIPPABLE, STRENGTH, 0, false}

#define DIAMOND_OF_DESTINY (Item) {'*', "Diamond of Destiny", CP_DIAMOND, NON_EQUIPPABLE, NONE, 0, false}

#define ITEMCATALOG (Item*[]) { \
    (Item[]) { DAGGER, DAGGER, DAGGER, HAND_AXE, CLOAK, CLOAK, LEATHER_ARMOR, SCROLL_LIGHT, POTION_HEALING, SCROLL_MAPPING },  \
    (Item[]) { DAGGER, HAND_AXE, HAND_AXE, SPEAR, LEATHER_ARMOR, LEATHER_ARMOR, RING_MAIL, POTION_STRENGTH, POTION_HEALING, SCROLL_TELEPORT },  \
    (Item[]) { HAND_AXE, SPEAR, SPEAR, SHORTSWORD, RING_MAIL, RING_MAIL, CHAIN_MAIL, SCROLL_TELEPORT, POTION_HEALING, POTION_INVISIBILITY },  \
    (Item[]) { SHORTSWORD, SHORTSWORD, SHORTSWORD, LONGSWORD, CHAIN_MAIL, CHAIN_MAIL, RING_MAIL, POTION_INVISIBILITY, POTION_STRENGTH, SCROLL_MAPPING },  \
    (Item[]) { LONGSWORD, LONGSWORD, LONGSWORD, SHORTSWORD, PLATE_MAIL, PLATE_MAIL, CHAIN_MAIL, POTION_HEALING, POTION_HEALING, POTION_STRENGTH },  \
}

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