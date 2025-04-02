#include <SDL2/SDL.h>
#include "game.h"
#include "constants.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Potapanje Brodova", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    bool running = true;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        renderGameScene(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
