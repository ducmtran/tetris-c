#include <SDL2/SDL.h>
#include "./render.h"
#include "./game.h"

void render_game_screen(SDL_Renderer *renderer) {
    SDL_Rect game_screen;
    game_screen.x = 200;
    game_screen.y = 0;
    game_screen.w = 400;
    game_screen.h = WINDOW_HEIGHT;
    // SDL_RenderSetViewport(renderer, &game_screen);
    SDL_SetRenderDrawColor(renderer, 76, 82, 78, 255);
    SDL_RenderFillRect(renderer, &game_screen);
}

void render_game_state(SDL_Renderer *renderer, game_t *game) {
    for (int block=0; block<240; block++) {
        int color = game->screen[block];
        if (color != EMPTY){
            render_block(renderer, block, color);
        }
    }
}

void render_block(SDL_Renderer *renderer, int block_number, int color) {
    SDL_Rect block;
    block.x = 200 + (block_number%10)*BLOCK_SIZE;
    int y = 920 - (block_number/10)*BLOCK_SIZE;
    block.y = y;
    block.w = BLOCK_SIZE;
    block.h = BLOCK_SIZE;
    // swtich all to positive value
    if (color < 0) { color = -color; }

    switch (color) {
        case ORANGE:
            SDL_SetRenderDrawColor(renderer, 244, 182, 66, 255);
            break;
        case YELLOW:
            SDL_SetRenderDrawColor(renderer, 255, 252, 76, 255);
            break;
        case BLUE:
            SDL_SetRenderDrawColor(renderer, 77, 45, 255, 255);
            break;
        case TEAL:
            SDL_SetRenderDrawColor(renderer, 109, 249, 255, 255);
            break;
        case PURPLE:
            SDL_SetRenderDrawColor(renderer, 249, 87, 247, 255);
            break;
        case RED:
            SDL_SetRenderDrawColor(renderer, 255, 76, 76, 255);
            break;
        case GREEN:
            SDL_SetRenderDrawColor(renderer, 109, 255, 102, 255);
            break;
    }
    SDL_RenderFillRect(renderer, &block);
}