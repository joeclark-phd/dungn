#include "game.h"

ItemVector* item_vector_create(void) {
    ItemVector* vec = calloc(1, sizeof(ItemVector));
    vec->items = calloc(ITEM_MAX_IN_VECTOR, sizeof(Item));
    vec->count = 0;
    return vec;
}
void item_vector_destroy(ItemVector* vec) {
    free(vec->items);
    free(vec);
}

bool item_add(ItemVector* vec, Item item) {
    if(vec->count >= ITEM_MAX_IN_VECTOR) {
        return false; // could not add another item
    } else {
        vec->items[vec->count] = item;
        vec->count += 1;
        return true;
    }
}

void item_remove(ItemVector vec, int index) {
    for(int i=index; i<vec.count-1; ++i) {
        // move all items left
        vec.items[i] = vec.items[i+1];
    }
    vec.count -= 1;
}

