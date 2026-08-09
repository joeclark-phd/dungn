#include "game.h"

Game* game_init(void) {
    Game* game = calloc(1, sizeof(Game));
    game->player = (Creature) {
        .y = LINES/2,
        .x = COLS/2,
        .symbol = '@'
    };
    game->level = level_init();
    return game;
}

void game_destroy(Game* game) {
    level_destroy(game->level);
    free(game);
}