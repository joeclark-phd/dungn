#include "game.h"

Game* game_init(void) {
    Game* game = calloc(1, sizeof(Game));
    game->player = (Creature) {
        .y = LINES/2,
        .x = COLS/2,
        .symbol = '@'
    };
    // creating map, etc
    return game;
}

void game_destroy(Game* game) {
    free(game);
}