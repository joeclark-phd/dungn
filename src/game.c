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
    return game;
}

void game_destroy(Game* game) {
    level_destroy(game->level);
    free(game);
}