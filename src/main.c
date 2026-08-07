#include "game.h"

void game_loop(void);

Game* game;

int main() {
    initscr(); // ncurses takes over the console
    curs_set(0); // cursor invisible
    noecho(); // dont' show user input on screen
    keypad(stdscr, TRUE); // allow special keys

    game = game_init();
    game_loop();
    game_destroy(game);

    endwin(); // return console to normal
    return 0;
}


void game_loop(void) {
    Creature* player = &game->player;
    player->pos.y = LINES/2;
    player->pos.x = COLS/2;

    draw_map();
    mvaddch(player->pos.y, player->pos.x, player->symbol);

    int ch;
    while((ch = getch())) {
        bool game_over = false;
        clear();
        switch(ch) {
            case 'q': game_over = true; break;
            case KEY_UP: --player->pos.y; break;
            case KEY_DOWN: ++player->pos.y; break;
            case KEY_LEFT: --player->pos.x; break;
            case KEY_RIGHT: ++player->pos.x; break;
        }

        draw_map();
        mvaddch(player->pos.y, player->pos.x, player->symbol);
        refresh();
        if(game_over) break;
    }
}