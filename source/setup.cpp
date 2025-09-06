#include "setup.h"
#include "rendering.h"
#include "constants.h"
#include "board.h"

#include <chrono>
#include <format>
#include <string>

static std::vector<ShipPart> shipParts;

Scene runSetupScene(SDL_Renderer* renderer,
                    FontSet& fonts,
                    GameState& gameState,
                    NetworkThread& network) {
    if (gameState.playerBoard == nullptr) {
        gameState.playerBoard = new Board(BOARD_SIZE);
    }

    auto frameTime = std::chrono::steady_clock::now();
    auto setupTime = std::chrono
                        ::duration_cast<std::chrono::seconds>
                        (frameTime - gameState.setupStartTime)
                        .count();
    int timeRemaining = SETUP_TIMELIMIT - static_cast<int>(setupTime);
    if (timeRemaining < 0) timeRemaining = 0;

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Scene::Quit;
        }
        if (timeRemaining > 0 &&
            event.type == SDL_MOUSEBUTTONDOWN &&
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

    if (timeRemaining == 0) {

       if (!gameState.serverResponsePending) {
           MessageMap shipPositions;
           shipPositions["type"] = "ShipPositions";

           int i = 0;
           for (const Ship& s : gameState.playerShips) {
               for (const ShipPart& sp : s.shipParts()) {
                   std::string position = std::format("X{}Y{}", sp.x, sp.y);
                   shipPositions[std::to_string(i)] = position;
                   i++;
               }
           }

           network.sendMessage(Message(shipPositions));
           gameState.serverResponsePending = true;
       } else {
           Message serverResponse = network.readMessage();

           if (static_cast<int>(setupTime) > SETUP_TIME_TOTAL ||
               serverResponse.isType("MatchQuit")) {
               gameState.serverResponsePending = false;

               delete gameState.playerBoard;
               gameState.playerBoard = nullptr;
               gameState.playerShips.clear();
               shipParts.clear();

               return Scene::MainMenu;
           }

           if (serverResponse.isType("MatchStart")) {
               gameState.serverResponsePending = false;

               gameState.isPlayerTurn = serverResponse.get("start-first") == "true";
               gameState.playerShipPoints = SHIP_POINTS_TOTAL;
               gameState.enemyShipPoints = SHIP_POINTS_TOTAL;
               shipParts.clear();

               gameState.turnStartTime = std::chrono::steady_clock::now();

               return Scene::Game;
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

    int minutes = timeRemaining / 60;
    int seconds = timeRemaining % 60;
    std::string timerText = std::format("{:02}:{:02}", minutes, seconds);

    renderText(renderer, fonts.font28, timerText,
               TIMER_SETUP_X, TIMER_SETUP_Y, white);

    SDL_RenderPresent(renderer);
    return Scene::Setup;
}
