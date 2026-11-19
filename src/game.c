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
        .xp = 0,
        .level = 1,
        .armorclass = 10,
        .max_attack = 3,
        .effect = NONE,
        .effect_duration = 0
    };
    game->turn = 0;
    game->monsters_killed = 0;
    game->deepest_level_reached = 1;
    game->status_log = calloc(24, sizeof(char*));
    game->status_log[0] = strdup("Welcome to the dungeon!");
    game->status_log[1] = strdup("Press ? for help, or P to see all messages.");
    game->last_status_index = 1;
    game->previous_last_status = 23;

    return game;
}

void game_destroy(Game* game) {
    for(int i=0; i<DN_DEPTH; ++i) {
        if(game->all_levels[i]) {
            free(game->all_levels[i]);
        }
    }
    free(game->all_levels);
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
        if(game->deepest_level_reached < game->current_depth+1) {
            game->deepest_level_reached = game->current_depth+1;
        }

        game->level = game->all_levels[game->current_depth];
        game->player.y = game->level->up_stair.y;
        game->player.x = game->level->up_stair.x;
    }
}

void attempt_up_stairs(Creature* player) {
    if(game->level->map[player->y][player->x].symbol != '<') {
        return;
    } else if(game->current_depth==0) {
        bool has_diamond = false;
        for(int i = 0; i<player->inventory->count; ++i) {
            if(player->inventory->items[i].symbol=='*') {
                has_diamond = true;
            }
        }
        char finalmessage[256];
        if(has_diamond) {
            snprintf(finalmessage, 254,
                "VICTORY\n\n"
                "You escaped the dungeon with the Diamond of Destiny,\n"
                "having played %d turns and killed %d monsters.\n"
                "You reached floor %d of the dungeon.",
                game->turn, game->monsters_killed, game->deepest_level_reached
            );
        } else {
            snprintf(finalmessage, 254,
                "DEFEAT\n\n"
                "You failed to obtain the Diamond of Destiny, but at least\n"
                "you escaped with your life.\n\n"
                "You played %d turns and killed %d monsters, reaching level %d\n"
                "of the dungeon.",
                game->turn, game->monsters_killed, game->deepest_level_reached
            );
        }
        finalmessage[255] = '\0';
        splash_screen(finalmessage);
        game->current_depth -= 1;
        return;
    } else {
        // player is on a up stair
        game->current_depth -= 1;
        game->level = game->all_levels[game->current_depth];
        game->player.y = game->level->down_stair.y;
        game->player.x = game->level->down_stair.x;
    }
}