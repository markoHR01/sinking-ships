#include "game.h"

Scene runGameScene(SDL_Renderer* renderer,
                   FontSet& fonts,
                   GameState& gameState) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Scene::Quit;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    return Scene::Game;
}
