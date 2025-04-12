#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "setup.h"
#include "constants.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font28 = nullptr;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Potapanje Brodova", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font28 = TTF_OpenFont("../assets/fonts/OpenSans-ExtraBold.ttf", 28);

    SDL_Event e;
    bool running = true;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        renderSetupScene(renderer, font28);
        SDL_Delay(16);
    }

    TTF_CloseFont(font28);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
