#include <ncurses.h>

// function declarations
void game_loop(void);

int main() {
    initscr(); // ncurses takes over the console
    curs_set(0); // cursor invisible
    noecho(); // dont' show user input on screen
    keypad(stdscr, TRUE); // allow special keys

    game_loop();

    endwin(); // return console to normal
    return 0;
}


void game_loop(void) {
    char player = '@';
    int player_y = LINES/2;
    int player_x = COLS/2;
    mvaddch(player_y, player_x, player);

    int ch;
    while((ch = getch())) {
        bool game_over = false;
        clear();
        switch(ch) {
            case 'q':
                game_over = true;
                break;
            case KEY_UP:
                --player_y;
                break;
            case KEY_DOWN:
                ++player_y;
                break;
            case KEY_LEFT:
                --player_x;
                break;
            case KEY_RIGHT:
                ++player_x;
                break;
        }
        mvaddch(player_y, player_x, player);
        refresh();
        if(game_over) break;
    }
}