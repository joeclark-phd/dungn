#include "game.h"

Game* game_init(void) {
    Game* game = calloc(1, sizeof(Game));
    game->level = level_init();
    Pos starting_pos = random_position_in_room(&game->level->rooms[0]);
    game->player = (Creature) {
        .y = starting_pos.y,
        .x = starting_pos.x,
        .symbol = '@'
    };
    game->turn = 0;

    game->status_log = calloc(24, sizeof(char*));
    game->status_log[0] = strdup("Welcome to the dungeon!");
    game->status_log[1] = strdup("Press P for all messages.");
    game->status_log[2] = strdup("There's a third message!");
    game->last_status_index = 2;
    game->previous_last_status = 23;

    return game;
}

void game_destroy(Game* game) {
    level_destroy(game->level);
    free(game->status_log);
    free(game);
}

void show_message_log(void) {
    clear();
    for(int i; i<24; ++i) {
        int j = game->last_status_index + 1 + i;
        if(game->status_log[j%24]) {
            mvprintw(i,0, game->status_log[j%24]);
        }
    }
    refresh();
}

void update_message_log_index(void) {
    game->previous_last_status = game->last_status_index;
}

void advance_message_log(void) {
    if((game->previous_last_status + 2)%24 <= game->last_status_index) {
        game->previous_last_status = game->previous_last_status + 2;
    }
}

