#include "game.h"

Game* game_init(void) {
    Game* game = calloc(1, sizeof(Game));
    game->all_levels = calloc(DN_DEPTH, sizeof(Level*));
    game->current_depth = 0;
    game->all_levels[0] = level_init(0);
    game->level = game->all_levels[0];
    game->player = (Creature) {
        .y = game->level->up_stair.y,
        .x = game->level->up_stair.x,
        .symbol = '@',
        .inventory = item_vector_create(),
        .maxhp = 10,
        .hp = 10,
        .thac0 = 20,
        .armorclass = 10,
        .max_attack = 3,
        .effect = NONE,
        .effect_duration = 0
    };
    game->turn = 0;

    game->status_log = calloc(24, sizeof(char*));
    game->status_log[0] = strdup("Welcome to the dungeon!");
    game->status_log[1] = strdup("Press ? for help, or P to see all messages.");
    game->last_status_index = 1;
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

void attempt_down_stairs(Creature* player) {
    if(game->level->map[player->y][player->x].symbol != '>') {
        return;
    } else {
        // player is on a down stair
        if(!game->all_levels[game->current_depth+1]) {
            // generate a new level
            game->all_levels[game->current_depth+1] = level_init(game->current_depth+1);
        }
        game->current_depth += 1;
        game->level = game->all_levels[game->current_depth];
        game->player.y = game->level->up_stair.y;
        game->player.x = game->level->up_stair.x;
    }
}

void attempt_up_stairs(Creature* player) {
    if(game->level->map[player->y][player->x].symbol != '<') {
        return;
    } else if(game->current_depth==0) {
        return;
        // TODO: end game
    } else {
        // player is on a up stair
        game->current_depth -= 1;
        game->level = game->all_levels[game->current_depth];
        game->player.y = game->level->down_stair.y;
        game->player.x = game->level->down_stair.x;
    }
}