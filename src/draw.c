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

    for(int i=0; i<2; ++i) {
        int j = game->previous_last_status + 1 + i;
        if(j%24 <= game->last_status_index) {
            mvprintw(22+i, 0, game->status_log[j%24]);
        }
    }
    if((game->previous_last_status+2)%24 < game->last_status_index) {
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

    init_pair(VISIBLE_TILE, PALE_YELLOW, COLOR_BLACK);
    init_pair(REMEMBERED_TILE, GRAY_BLUE, COLOR_BLACK);
}