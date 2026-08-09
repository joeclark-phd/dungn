#include "game.h"

// function declarations
void game_loop(void);

Game* game;

int main() {
    initscr(); // ncurses takes over the console
    curs_set(0); // cursor invisible
    noecho(); // don't show user input on screen
    keypad(stdscr, TRUE); // allow special keys

    game = game_init();
    game_loop();
    game_destroy(game);

    endwin(); // return console to normal
    return 0;
}


void game_loop(void) {
    Creature* player = &game->player;
    draw_everything();

    int ch;
    while((ch = getch())) {
        bool game_over = false;
        clear();
        switch(ch) {
            case 'q': game_over = true; break;
            case KEY_UP: --player->y; break;
            case KEY_DOWN: ++player->y; break;
            case KEY_LEFT: --player->x; break;
            case KEY_RIGHT: ++player->x; break;
        }
        draw_everything();
        refresh();
        if(game_over) break;
    }
}