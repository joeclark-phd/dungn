#include "game.h"

void draw_map(Tile** map);
void draw_player(Creature* player);

Game* game;

void draw_everything(void) {
    Tile** map = game->level->map;
    Creature* player = &game->player;

    draw_map(map);
    draw_player(player);
    mvprintw(0,0,"Welcome to the Dungeon. Use arrow keys to move.");
    mvprintw(0,76,"%4d", game->turn);

    // show message(s)
    int num_messages = ((game->last_status_index+24) - game->previous_last_status) % 24;
    for(int i=0; i<num_messages && i<2; ++i) {
        int j = (game->previous_last_status + 1 + i) % 24;
        mvprintw(22+i, 0, game->status_log[j]);
    }
    if(num_messages>2) {
        attron(COLOR_PAIR(REMEMBERED_TILE));
        mvprintw(23,72,"[(m)ore]");
        attroff(COLOR_PAIR(REMEMBERED_TILE));
    }

}

void draw_map(Tile** map) {
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            if(map[y][x].visible) {
                mvaddch(y+DRAW_MAP_Y,x,map[y][x].symbol | COLOR_PAIR(VISIBLE_TILE));
                if(map[y][x].items && map[y][x].items->count>0) {
                    Item i = map[y][x].items->items[ map[y][x].items->count-1 ];
                    mvaddch(y+DRAW_MAP_Y, x, i.symbol | COLOR_PAIR(i.color));
                }
            } else if (map[y][x].remembered) {
                mvaddch(y+DRAW_MAP_Y,x,map[y][x].symbol | COLOR_PAIR(REMEMBERED_TILE));
            }
            
        }
    }
}

void draw_player(Creature* player) {
    mvaddch(player->y+DRAW_MAP_Y, player->x, player->symbol);
}

void setup_colors(void) {
    init_color(GRAY_BLUE, 400, 600, 700);
    init_color(PALE_YELLOW, 1000, 1000, 750);

    init_color(HONEY_GOLD, 1000, 900, 0);
    init_color(BLOOD_RED, 750, 0, 0);
    init_color(ROYAL_PURPLE, 500, 0, 1000);
    init_color(OGRE_GREEN, 0, 750, 0);
    init_color(OWLBEAR_BROWN, 500, 250, 700);
    init_color(TIGER_ORANGE, 1000, 500, 0);
    init_color(FROST_BLUE, 0, 250, 1000);
    init_color(POTION_CYAN, 0, 1000, 1000);
    init_color(STEEL_GRAY, 600, 600, 600);
    init_color(BONE_WHITE, 1000, 1000, 1000);

    init_pair(CP_GOLD, HONEY_GOLD, COLOR_BLACK);
    init_pair(CP_RED, BLOOD_RED, COLOR_BLACK);
    init_pair(CP_PURPLE, ROYAL_PURPLE, COLOR_BLACK);
    init_pair(CP_GREEN, OGRE_GREEN, COLOR_BLACK);
    init_pair(CP_BROWN, OWLBEAR_BROWN, COLOR_BLACK);
    init_pair(CP_ORANGE, TIGER_ORANGE, COLOR_BLACK);
    init_pair(CP_BLUE, FROST_BLUE, COLOR_BLACK);
    init_pair(CP_CYAN, POTION_CYAN, COLOR_BLACK);
    init_pair(CP_GRAY, STEEL_GRAY, COLOR_BLACK);
    init_pair(CP_WHITE, BONE_WHITE, COLOR_BLACK);

    init_pair(VISIBLE_TILE, PALE_YELLOW, COLOR_BLACK);
    init_pair(REMEMBERED_TILE, GRAY_BLUE, COLOR_BLACK);
}