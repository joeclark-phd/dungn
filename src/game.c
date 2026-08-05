#include "game.h"

Game* game_init(void) {
    Game* game = calloc(1, sizeof(Game));
    game->player = (Creature) { '@', "Sir Atsign", (Pos) {10,10} };
    game->turn = 0;
    game->dungeon_level = 0;
    return game;
}

void game_destroy(Game* game) {
    free(game);
};