#include "menu.h"
#include "constants.h"
#include "rendering.h"

void renderMainMenu(SDL_Renderer* renderer,
                    TTF_Font* font86,
                    TTF_Font* font24,
                    bool inQueue) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    renderText(renderer, font86, "Potapanje", TITLE_TOP_X, TITLE_TOP_Y, white);
    renderText(renderer, font86, "Brodova", TITLE_BOTTOM_X, TITLE_BOTTOM_Y, white);

    SDL_Rect button = {BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H};
    SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255);
    SDL_RenderFillRect(renderer, &button);

    if (inQueue) {
        renderText(renderer, font24, "Odustani",
                   BUTTON_X + BUTTON_W / 2, BUTTON_Y + BUTTON_H / 2, white);

        renderLoadingAnimation(renderer, LOAD_ANIMATION_X, LOAD_ANIMATION_Y,
                               LOAD_SQUARE_SIZE, LOAD_INTERVAL);
    } else {
        renderText(renderer, font24, "Igraj",
                   BUTTON_X + BUTTON_W / 2, BUTTON_Y + BUTTON_H / 2, white);
    }

    SDL_RenderPresent(renderer);
}
