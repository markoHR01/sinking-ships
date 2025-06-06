#include "menu.h"
#include "rendering.h"
#include "constants.h"

Scene runMainMenu(SDL_Renderer* renderer,
                  FontSet& fonts,
                  GameState& gameState,
                  NetworkThread& network) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Scene::Quit;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            SDL_Rect button = {BUTTON_X, BUTTON_Y,
                               BUTTON_W, BUTTON_H};
            SDL_Point mouse = {mouseX, mouseY};
            if (SDL_PointInRect(&mouse, &button)) {
                gameState.inQueue = !gameState.inQueue;

                return Scene::MainMenu;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    renderText(renderer, fonts.font86, "Potapanje", TITLE_TOP_X, TITLE_TOP_Y, white);
    renderText(renderer, fonts.font86, "Brodova", TITLE_BOTTOM_X, TITLE_BOTTOM_Y, white);

    SDL_Rect button = {BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H};
    SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255);
    SDL_RenderFillRect(renderer, &button);

    if (gameState.inQueue) {
        renderText(renderer, fonts.font24, "Odustani",
                   BUTTON_X + BUTTON_W / 2, BUTTON_Y + BUTTON_H / 2, white);

        renderLoadingAnimation(renderer, LOAD_ANIMATION_X, LOAD_ANIMATION_Y,
                               LOAD_SQUARE_SIZE, LOAD_INTERVAL);
    } else {
        renderText(renderer, fonts.font24, "Igraj",
                   BUTTON_X + BUTTON_W / 2, BUTTON_Y + BUTTON_H / 2, white);
    }

    SDL_RenderPresent(renderer);
    return Scene::MainMenu;
}
