#include "setup.h"
#include "rendering.h"
#include "constants.h"
#include "board.h"

static std::vector<ShipPart> shipParts;

Scene runSetupScene(SDL_Renderer* renderer,
                    FontSet& fonts,
                    GameState& gameState,
                    NetworkThread& network) {
    if (gameState.playerBoard == nullptr) {
        gameState.playerBoard = new Board(BOARD_SIZE);
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Scene::Quit;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN &&
            gameState.playerShips.size() < SHIP_LIST.size()) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            int x = (mouseX - BOARD_SETUP_X) / SECTOR_SIZE;
            int y = (mouseY - BOARD_SETUP_Y) / SECTOR_SIZE;

            if (x >= 0 && x < BOARD_SIZE &&
                y >= 0 && y < BOARD_SIZE) {
                Board& playerBoard = *gameState.playerBoard;

                if (playerBoard(x, y) == Token::Empty) {
                    playerBoard(x, y, Token::PlayerShip);

                    shipParts.push_back(ShipPart(x, y));

                    int newShipIndex = gameState.playerShips.size();
                    size_t newShipSize = static_cast<size_t>(
                                         SHIP_LIST.at(newShipIndex));
                    if (shipParts.size() == newShipSize) {
                        if (shipIsValid(shipParts)) {
                            gameState.playerShips
                                     .push_back(Ship(shipParts));
                        } else {
                            for (const ShipPart& sp : shipParts) {
                                playerBoard(sp.x, sp.y, Token::Empty);
                            }
                        }

                        shipParts.clear();
                    }
                }
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderBoard(renderer, fonts.font28, BOARD_SETUP_X, BOARD_SETUP_Y,
                (*gameState.playerBoard), SECTOR_SIZE);

    SDL_Color green = {50, 150, 50, 255};

    renderText(renderer, fonts.font28, "5. Nosač Zrakoplova (5X)",
               SHIP_SETUP_X, SHIP_SETUP_Y, green);
    renderText(renderer, fonts.font28, "4. Bojni Brod (4X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD, green);
    renderText(renderer, fonts.font28, "3. Krstarica (3X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD * 2, green);
    renderText(renderer, fonts.font28, "2. Podmornica (3X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD * 3, green);
    renderText(renderer, fonts.font28, "1. Razarač (2X)",
               SHIP_SETUP_X, SHIP_SETUP_Y + SHIP_SETUP_YADD * 4, green);

    SDL_Color white = {255, 255, 255, 255};

    renderText(renderer, fonts.font28, "00:45",
               TIMER_SETUP_X, TIMER_SETUP_Y, white);

    SDL_RenderPresent(renderer);
    return Scene::Setup;
}
