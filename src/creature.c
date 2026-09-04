#include "game.h"

Game* game;

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
    // create a window
    WINDOW* inv_win = newwin(22,78,2,0);
    box(inv_win, 0, 0);
    int ch;
    do {
        if(c->inventory) {
            for(int i=0; i<c->inventory->count; ++i) {
                mvwprintw(inv_win, i+1, 1, "%s", c->inventory->items[i].name);
            }
        }

        wrefresh(inv_win);
    } while((ch=getch()) != 'i');
    delwin(inv_win);
}