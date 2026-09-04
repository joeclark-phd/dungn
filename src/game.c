#include "game.h"

Game* game_init(void) {
    Game* game = calloc(1, sizeof(Game));
    game->level = level_init();
    Pos starting_pos = random_position_in_room(&game->level->rooms[0]);
    game->player = (Creature) {
        .y = starting_pos.y,
        .x = starting_pos.x,
        .symbol = '@',
        .inventory = item_vector_create()
    };
    game->turn = 0;

    game->status_log = calloc(24, sizeof(char*));
    game->status_log[0] = strdup("Welcome to the dungeon!");
    game->status_log[1] = strdup("Press P to see all messages.");
    game->status_log[2] = strdup("There's a third message here!");
    game->last_status_index = 2;
    game->previous_last_status = 23;

    return game;
}

void game_destroy(Game* game) {
    level_destroy(game->level);
    for(int i=0; i<24; ++i) {
        if(game->status_log[i]) {
            free(game->status_log[i]);
        }
    }
    free(game->status_log);
    item_vector_destroy(game->player.inventory);
    free(game);
}

void show_message_log(void) {
    clear();
    for(int i=0; i<24; ++i) {
        int j = game->last_status_index + 1 + i;
        if(game->status_log[j%24]) {
            mvprintw(i,0,game->status_log[j%24]);
        }
    }
    refresh();
}

void advance_message_log(void) {
    int num_messages = ((game->last_status_index+24) - game->previous_last_status) % 24;
    if(num_messages>2) {
        game->previous_last_status = (game->previous_last_status+2)%24;
    }
}

void flush_message_log(void) {
    game->previous_last_status = game->last_status_index;
}

void add_message(char* message) {
    int i = (game->last_status_index + 1)%24;
    if(game->status_log[i]) {
        free(game->status_log[i]);
    }
    game->status_log[i] = strdup(message);
    game->last_status_index = i;
}
