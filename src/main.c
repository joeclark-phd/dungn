#include "game.h"

// function declarations
void game_loop(void);

Game* game;

int main() {
    srand(time(NULL));

    initscr(); // ncurses takes over the console
    curs_set(0); // cursor invisible
    noecho(); // don't show user input on screen
    keypad(stdscr, TRUE); // allow special keys

    if(!has_colors() && can_change_color()) {
        printf("Sorry, your terminal doesn't support colors. Exiting.");
        return 1;
    }

    start_color();
    setup_colors();

    game = game_init();
    game_loop();
    game_destroy(game);

    endwin(); // return console to normal
    return 0;
}


void game_loop(void) {
    Creature* player = &game->player;
    do_fov();
    draw_everything();

    int ch;
    while((ch = getch())) {
        bool game_over = false;
        bool turn_taken = false;
        clear();
        switch(ch) {
            case 'q': game_over = true; break;
            case 'P': show_message_log(); getch(); clear(); break;
            case 'm': advance_message_log(); break;
            case KEY_UP: case '8': turn_taken = attempt_move(player, -1, 0); break;
            case KEY_DOWN: case '2': turn_taken = attempt_move(player, 1, 0); break;
            case KEY_LEFT: case '4': turn_taken = attempt_move(player, 0, -1); break;
            case KEY_RIGHT: case '6': turn_taken = attempt_move(player, 0, 1); break;
            case '7': turn_taken = attempt_move(player, -1, -1); break;
            case '9': turn_taken = attempt_move(player, -1, 1); break;
            case '1': turn_taken = attempt_move(player, 1, -1); break;
            case '3': turn_taken = attempt_move(player, 1, 1); break;
        }
        if(turn_taken) {
            // monsters move, etc.
            ++game->turn;
            update_message_log_index();
        }
        do_fov();
        draw_everything();
        refresh();
        if(game_over) break;
    }
}