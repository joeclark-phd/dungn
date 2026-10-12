#include "game.h"

Game* game;

void drop_item(Creature* c, int selection);
void equip_item(Creature* c, int selection);



CreatureVector* creature_vector_create(void) {
    CreatureVector* vec = calloc(1, sizeof(CreatureVector));
    vec->creatures = calloc(DN_CREATURES_PER_LEVEL, sizeof(Creature));
    vec->count = 0;
    return vec;
}
void creature_vector_destroy(CreatureVector* vec) {
    free(vec->creatures);
    free(vec);
}
void creature_add(CreatureVector* vec, Creature c) {
    if(vec->count >= DN_CREATURES_PER_LEVEL) {
        return;
    }
    vec->creatures[vec->count] = c;
    vec->count += 1;
}
void creature_remove(CreatureVector* vec, int index) {
    if(index+1 < vec->count) {
        // a swapback array
        vec->creatures[index] = vec->creatures[vec->count-1];
    }
    vec->count -= 1;
}




bool attempt_move(Creature* c, int dy, int dx) {
    flush_message_log();
    int newy = c->y + dy;
    int newx = c->x + dx;
    // check if walkable tile
    Tile** map = game->level->map;
    if(map[newy][newx].walkable) {
        c->y = newy;
        c->x = newx;

        // check if any items there
        Tile* new_tile = &map[newy][newx];
        if(new_tile->items) {
            for(int i=0; i<new_tile->items->count; ++i) {
                char message[80];
                snprintf(message, 80, "Found a %s.", new_tile->items->items[i].name);
                add_message(message);
            }
        }


        return true;
    }
    // move failed
    add_message("You bumped into a wall.");
    return false;
}

bool pick_up_item(Creature* c) {
    flush_message_log();
    if(!c->inventory) { return false; }

    Tile** map = game->level->map;
    Tile* new_tile = &map[c->y][c->x];
    if(new_tile->items && new_tile->items->count > 0) {
        Item item = new_tile->items->items[new_tile->items->count-1];
        if (item_add(c->inventory, item)) {
            item_remove(new_tile->items, new_tile->items->count-1);
            char message[80];
            snprintf(message, 80, "Picked up a %s.", item.name );
            add_message(message);
            return true;
        } else {
            add_message("Can't pick up. Your inventory is full.");
            return false;
        }
    }
    return false;
}

void open_inventory(Creature* c) {
    flush_message_log();

    // create a window
    WINDOW* inv_win = newwin(23,80,1,0);
    keypad(inv_win, TRUE); // allow special keys
    box(inv_win, 0, 0);
    mvwprintw(inv_win, 0, 5, "INVENTORY");
    mvwprintw(inv_win, 22, 15, "Press (d) to drop, (w) to wield/wear, or (i) to close inventory.");
    int ch;
    int selection = 0;
    do {
        switch(ch) {
            case '8': case KEY_UP: if(selection > 0) --selection; break;
            case '2': case KEY_DOWN: if(c->inventory && selection+1 < c->inventory->count) ++selection; break;
            case 'd':
                if(c->inventory && c->inventory->count>0) {
                    drop_item(c, selection);
                    // list is shorter, blank the last line
                    mvwprintw(inv_win, c->inventory->count+1, 1,  "%-78s", "");
                    if(selection >= c->inventory->count) --selection;
                }
                break;
            case 'w':
                if(c->inventory && c->inventory->count>0) {
                    equip_item(c, selection);
                }
                break;
        }
        if(c->inventory && c->inventory->count>0) {
            for(int i=0; i<c->inventory->count; ++i) {
                if(c->inventory->items[i].equipped) {
                    wattron(inv_win, COLOR_PAIR(CP_GOLD));
                }
                if(i==selection) {
                    wattron(inv_win, A_REVERSE);
                    mvwprintw(inv_win, i+1, 1, "%s", c->inventory->items[i].name);
                    wattroff(inv_win, A_REVERSE);
                } else {
                    mvwprintw(inv_win, i+1, 1, "%s", c->inventory->items[i].name);
                }
                wattroff(inv_win, COLOR_PAIR(CP_GOLD));
            }
        } else {
            mvwprintw(inv_win, 1,1, "Player inventory is empty.");
        }

        wrefresh(inv_win);
    } while((ch=wgetch(inv_win)) != 'i');
    delwin(inv_win);
}

void drop_item(Creature* c, int selection) {

    Tile** map = game->level->map;
    Tile* t = &map[c->y][c->x];
    ItemVector* inv = c->inventory;
    if(!t->items) {
        t->items = item_vector_create();
    }
    Item it = inv->items[selection];
    item_remove(inv, selection);
    item_add(t->items, it);
    char message[80];
    snprintf(message, 80, "Dropped a %s.", it.name );
    add_message(message);    
}

void equip_item(Creature* c, int selection) {
    ItemVector* inv = c->inventory;
    Item it = inv->items[selection];
    if(it.type==NON_EQUIPPABLE) {
        return;
    }
    if(it.equipped) {
        // un-equip it
        inv->items[selection].equipped = false;
        char message[80];
        snprintf(message, 80, "You un-equip the %s.", it.name );
        add_message(message);
    } else {
        // un-equip all others of the type
        for(int i=0; i<inv->count; ++i) {
            if(inv->items[i].type == it.type) {
                inv->items[i].equipped = false;
            }
        }
        // equip this item
        inv->items[selection].equipped = true;
        char message[80];
        snprintf(message, 80, "You equip the %s.", it.name );
        add_message(message);
    }
}