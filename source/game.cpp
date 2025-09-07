#include "game.h"
#include "rendering.h"
#include "constants.h"
#include "board.h"

#include <array>
#include <string>
#include <format>
#include <chrono>

Scene runGameScene(SDL_Renderer* renderer,
                   FontSet& fonts,
                   GameState& gameState,
                   NetworkThread& network) {
    if (gameState.enemyBoard == nullptr) {
        gameState.enemyBoard = new Board(BOARD_SIZE);
    }

    auto frameTime = std::chrono::steady_clock::now();
    auto turnTime = std::chrono
                       ::duration_cast<std::chrono::seconds>
                       (frameTime - gameState.turnStartTime)
                       .count();
    int timeRemaining = TURN_TIMELIMIT - static_cast<int>(turnTime);
    if (timeRemaining < 0) timeRemaining = 0;

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Scene::Quit;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            SDL_Rect button = {EXIT_BUTTON_X, EXIT_BUTTON_Y,
                               EXIT_BUTTON_W, EXIT_BUTTON_H};
            SDL_Point mouse = {mouseX, mouseY};
            if (SDL_PointInRect(&mouse, &button)) {
                gameState.serverResponsePending = false;

                gameState.playerShipSunk.fill(false);
                gameState.enemyShipSunk.fill(false);

                delete gameState.enemyBoard;
                gameState.enemyBoard = nullptr;
                delete gameState.playerBoard;
                gameState.playerBoard = nullptr;
                gameState.playerShips.clear();

                return Scene::MainMenu;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN
            timeRemaining > 0 &&
            !gameState.serverResponsePending &&
            !gameState.isGameOver() &&
            gameState.isPlayerTurn()) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            int x = (mouseX - ENEMY_BOARD_X) / SECTOR_SIZE;
            int y = (mouseY - ENEMY_BOARD_Y) / SECTOR_SIZE;

            if (x >= 0 && x < BOARD_SIZE &&
                y >= 0 && y < BOARD_SIZE) {
                Board& enemyBoard = *gameState.enemyBoard;

                if (enemyBoard(x, y) == Token::Empty) {
                    MessageMap attack;
                    attack["type"] = "Attack";
                    attack["X"] = std::to_string(x);
                    attack["Y"] = std::to_string(y);

                    network.sendMessage(Message(attack));
                    gameState.serverResponsePending = true;
                }
            }
        }
    }

    Message serverResponse = network.readMessage();

    if (serverResponse.isType("AttackResult")) {
        gameState.serverResponsePending = false;
        gameState.isPlayerTurn = false;

        gameState.turnStartTime = std::chrono::steady_clock::now();

        Board& enemyBoard = *gameState.enemyBoard;

        if (serverResponse.get("hit") == "false") {
            enemyBoard(x, y, Token::Miss);
        } else {
            int x = std::stoi(serverResponse.get("X"));
            int y = std::stoi(serverResponse.get("Y"));
            enemyBoard(x, y, Token::EnemyShip);
            gameState.enemyShipPoints -= 1;

            if (serverResponse.get("sunk") == "true") {
                int i = std::stoi(serverResponse.get("sunk-index"));
                gameState.enemyShipSunk[i] = true;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderBoard(renderer, fonts.font28, PLAYER_BOARD_X, PLAYER_BOARD_Y,
                (*gameState.playerBoard), SECTOR_SIZE);
    renderBoard(renderer, fonts.font28, ENEMY_BOARD_X, ENEMY_BOARD_Y,
                (*gameState.enemyBoard), SECTOR_SIZE);

    SDL_Color green = {50, 150, 50, 255};
    SDL_Color red   = {150, 50, 50, 255};
    SDL_Color gray  = {150, 150, 150, 255};

    std::array<std::string, 5> shipNames = {
        "5. Nosač Zrakoplova (5X)",
        "4. Bojni Brod (4X)",
        "3. Krstarica (3X)",
        "2. Podmornica (3X)",
        "1. Razarač (2X)"
    };

    for (size_t i = 0; shipNames.size(); ++i) {
        SDL_Color shipColor = gameState.playerShipSunk[i] ? gray : green;
        renderText(renderer, fonts.font24, shipNames[i],
                   PLAYER_SHIPS_X, PLAYER_SHIPS_Y + SHIP_GAME_YADD * i, shipColor);
    }

    for (size_t i = 0; shipNames.size(); ++i) {
        SDL_Color shipColor = gameState.enemyShipSunk[i] ? gray : red;
        renderText(renderer, fonts.font24, shipNames[i],
                   ENEMY_SHIPS_X, ENEMY_SHIPS_Y + SHIP_GAME_YADD * i, shipColor);
    }

    auto playerPoints = "(" + std::to_string(gameState.playerShipPoints) + ")";
    auto enemyPoints = "(" + std::to_string(gameState.enemyShipPoints) + ")";

    renderText(renderer, fonts.font28, playerPoints,
               PLAYER_FLEET_X, PLAYER_FLEET_Y, green);
    renderText(renderer, fonts.font28, enemyPoints,
               ENEMY_FLEET_X, ENEMY_FLEET_Y, red);

    std::string timerText;
    SDL_Color timerColor;
    if (!gameState.isGameOver()) {
        int minutes = timeRemaining / 60;
        int seconds = timeRemaining % 60;
        timerText = std::format("{:02}:{:02}", minutes, seconds);
        timerColor = gameState.isPlayerTurn ? green : red;
    } else {
        if (gameState.playerShipPoints == 0) {
            timerText = "Poraz";
            timerColor = red;
        } else {
            timerText = "Pobjeda";
            timerColor = green;
        }
    }

    renderText(renderer, fonts.font28, timerText,
               TIMER_GAME_X, TIMER_GAME_Y, timerColor);

    SDL_Rect exitButton = {EXIT_BUTTON_X, EXIT_BUTTON_Y,
                           EXIT_BUTTON_W, EXIT_BUTTON_H};
    SDL_SetRenderDrawColor(renderer, 10, 10, 50, 255);
    SDL_RenderFillRect(renderer, &exitButton);

    SDL_Color white = {255, 255, 255, 255};

    renderText(renderer, fonts.font24, "Završi",
               EXIT_BUTTON_X + EXIT_BUTTON_W / 2,
               EXIT_BUTTON_Y + EXIT_BUTTON_H / 2,
               white);

    SDL_RenderPresent(renderer);
    return Scene::Game;
}
