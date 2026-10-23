#include "game.h"

// function declarations
void game_loop(void);
void splash_screen(char* message);
bool dialog(char* message);

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

    splash_screen(
        "\n\n\n\n    DUNGEON OF DESTINY"
        "\n\n    The ruins outside of town are said to be the remains"
        "\n    of an ancient wizard's tower.  Somewhere deep below"
        "\n    is the resting place of the DIAMOND OF DESTINY, a"
        "\n    legendary artifact with the power to alter fate itself."
        "\n\n    Many have entered the tunnels, none have returned."
        "\n    Will you be the one to claim this treasure?"
    );
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
            case 'q': game_over = dialog("Are you sure you want to quit?"); break;
            case 'P': show_message_log(); getch(); clear(); break;
            case 'm': advance_message_log(); break;
            case 'g': turn_taken = pick_up_item(player); break;
            case 'i': open_inventory(player); break;
            case '?': splash_screen(
                "ABOUT THE GAME\n\n"
                "To move around: arrow keys or numerical keyboard\n\n"
                "Other commands:\n"
                " (g) pick up item\n"
                " (i) open inventory\n"
                " (P) show prior messages\n"
                " (?) open this help screen\n"
                " (q) quit"
            ); break;
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
            if(game->turn % 10 == 0) {
                // regenerate
                if(player->hp<player->maxhp) ++player->hp;
            }
            monsters_move();
        }
        do_fov();
        draw_everything();
        refresh();
        if(player->hp <= 0) {
            splash_screen("You are dead!");
            game_over = true;
        }
        if(game_over) break;
    }
}


void splash_screen(char* message) {
    clear();
    box(stdscr, 0, 0);
    refresh();
    WINDOW* splash = newwin(22,78,1,1);

    mvwprintw(splash, 0, 0, message);
    mvwprintw(splash, 21, 50, "Press any Key to continue");
    wrefresh(splash);
    
    wgetch(splash);
    delwin(splash);
    clear();
}

bool dialog(char* message) {
    WINDOW* dialog = newwin(7,60,8,10);
    box(dialog,0,0);
    mvwprintw(dialog, 2, 2, message);
    mvwprintw(dialog, 4, 42, "[Y]es     [N]o");
    int ch;
    bool answer = false;
    while((ch = wgetch(dialog))) {
        if(ch=='y'||ch=='Y') {
            answer = true;
            break;
        }
        if(ch=='n'||ch=='N') {
            answer = false;
            break;
        }
    };
    delwin(dialog);
    return answer;
}