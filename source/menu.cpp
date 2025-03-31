#include "menu.h"
#include "constants.h"
#include "rendering.h"

void renderMainMenu(SDL_Renderer* renderer,
                    TTF_Font* titleFont,
                    TTF_Font* buttonFont,
                    bool inQueue) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    renderText(renderer, titleFont, "Potapanje", TITLE_TOP_X, TITLE_TOP_Y, white);
    renderText(renderer, titleFont, "Brodova", TITLE_BOTTOM_X, TITLE_BOTTOM_Y, white);

    SDL_Rect button = {BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H};
    SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255);
    SDL_RenderFillRect(renderer, &button);

    if (inQueue) {
        renderText(renderer, buttonFont, "Odustani", BUTTON_QUIT_X, BUTTON_QUIT_Y, white);

        renderLoadingAnimation(renderer, LOAD_ANIMATION_X, LOAD_ANIMATION_Y,
                               LOAD_SQUARE_SIZE, LOAD_INTERVAL);
    } else {
        renderText(renderer, buttonFont, "Igraj", BUTTON_PLAY_X, BUTTON_PLAY_Y, white);
    }

    SDL_RenderPresent(renderer);
}
