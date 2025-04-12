#include "setup.h"
#include "rendering.h"
#include "client.h"
#include "constants.h"

void renderSetupScene(SDL_Renderer* renderer,
                      TTF_Font* font28) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Board board(BOARD_SIZE);

    renderBoard(renderer, font28,
                BOARD_SETUP_X, BOARD_SETUP_Y, board, SECTOR_SIZE);

    SDL_Color green = {50, 150, 50, 255};

    renderText(renderer, font28, "5. Nosač Zrakoplova (5X)",
               SHIP_SETUP_X, SHIP_SETUP_Y, green);
    renderText(renderer, font28, "4. Bojni brod (4X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD, green);
    renderText(renderer, font28, "3. Krstarica (3X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD * 2, green);
    renderText(renderer, font28, "2. Podmornica (3X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD * 3, green);
    renderText(renderer, font28, "1. Razarač (2X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD * 4, green);

    SDL_Color white = {255, 255, 255, 255};

    renderText(renderer, font28, "00:45",
               TIMER_SETUP_X, TIMER_SETUP_Y, white);

    SDL_RenderPresent(renderer);
}
