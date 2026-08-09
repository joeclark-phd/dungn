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

}

void draw_map(Tile** map) {
    for(int y=0; y<DN_HEIGHT; ++y) {
        for(int x=0; x<DN_WIDTH; ++x) {
            mvaddch(y+DRAW_MAP_Y,x,map[y][x].symbol);
        }
    }
}

void draw_player(Creature* player) {
    mvaddch(player->y+DRAW_MAP_Y, player->x, player->symbol);
}