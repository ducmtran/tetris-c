#ifndef RENDER_H_
#define RENDER_H_

#include "./game.h"

#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 800

#define GAME_VIEW_X 200
#define GAME_VIEW_Y 0

#define BLOCK_SIZE 40

void render_game_screen(SDL_Renderer *renderer);

void render_game_state(SDL_Renderer *renderer, game_t *game);

SDL_Rect* game_screen_init();

#endif