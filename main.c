// tetris game first file

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "./game.h"
#include "./render.h"

int main(int argc, char *args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Tetris", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // initialize array for game screen
    int screen[W*H];

    game_t game = {
        .screen = screen,
        .score = 0,
        .state = 1,
        .speed = 2
    };

    // add 50 to account for not yet visible piece
    for (int i=0; i<(W*H)+50; i++) {
        game.screen[i] = 0;
    }
    piece_t *piece;
    srand(time(NULL));
    piece_t sth = random_piece();
    piece = &sth;

    SDL_Event e;
    int quit = 0;
    unsigned int lastTime, current, elapsed;
    lastTime = SDL_GetTicks();
    while (quit == 0) {
        current = SDL_GetTicks();
        elapsed = current - lastTime;
        lastTime = current;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.scancode) {
                        case SDL_SCANCODE_RETURN:
                            if (game.state == 0) { game.state = 1; }
                            else { game.state = 0; }
                            break;
                        case SDL_SCANCODE_LEFT:
                            move_left(&game, piece);
                            break;
                        case SDL_SCANCODE_RIGHT:
                            move_right(&game, piece);
                            break;
                        case SDL_SCANCODE_UP:
                            rotate(&game, piece);
                            break;
                        case SDL_SCANCODE_DOWN:
                            drop(&game, piece);
                            break;
                        case SDL_SCANCODE_SPACE:
                            hard_drop(&game, piece);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                default:
                    break;
            }
            // handle input with switch?
        }

        // update game state?
        if (game.state == 1) {
            update(&game, piece, elapsed);
        }

        // render game here?
        SDL_SetRenderDrawColor(renderer, 0, 123, 0, 255);
        // SDL_RenderFillRect(renderer, NULL);
        SDL_RenderClear(renderer);
        render_game_screen(renderer);

        render_game_state(renderer, &game);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

