#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "constants.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font86 = nullptr;
TTF_Font* font24 = nullptr;

bool inQueue = false;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Potapanje Brodova", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font86 = TTF_OpenFont("assets/fonts/OpenSans-ExtraBold.ttf", 86);
    font24 = TTF_OpenFont("assets/fonts/OpenSans-ExtraBold.ttf", 24);

    SDL_Event e;
    bool running = true;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Rect button = {BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H};
                if (x >= button.x && x <= button.x + button.w &&
                    y >= button.y && y <= button.y + button.h) {
                    inQueue = !inQueue;
                }
            }
        }
        renderMainMenu(renderer, font86, font24, inQueue);
        SDL_Delay(16);
    }

    TTF_CloseFont(font86);
    TTF_CloseFont(font24);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
