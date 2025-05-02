#include "game.h"
#include "rendering.h"
#include "constants.h"
#include "board.h"

Scene runGameScene(SDL_Renderer* renderer,
                   FontSet& fonts,
                   GameState& gameState) {
    if (gameState.enemyBoard == nullptr) {
        gameState.enemyBoard = new Board(BOARD_SIZE);
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Scene::Quit;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            int x = (mouseX - ENEMY_BOARD_X) / SECTOR_SIZE;
            int y = (mouseY - ENEMY_BOARD_Y) / SECTOR_SIZE;

            if (x >= 0 && x < BOARD_SIZE &&
                y >= 0 && y < BOARD_SIZE) {
                Board& enemyBoard = *gameState.enemyBoard;

                if (enemyBoard(x, y) == Token::Empty) {
                    enemyBoard(x, y, Token::Miss);
                }
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

    renderText(renderer, fonts.font24, "5. Nosač Zrakoplova (5X)",
               PLAYER_SHIPS_X, PLAYER_SHIPS_Y, green);
    renderText(renderer, fonts.font24, "4. Bojni Brod (4X)",
               PLAYER_SHIPS_X, PLAYER_SHIPS_Y + SHIP_GAME_YADD, green);
    renderText(renderer, fonts.font24, "3. Krstarica (3X)",
               PLAYER_SHIPS_X, PLAYER_SHIPS_Y + SHIP_GAME_YADD * 2, green);
    renderText(renderer, fonts.font24, "2. Podmornica (3X)",
               PLAYER_SHIPS_X, PLAYER_SHIPS_Y + SHIP_GAME_YADD * 3, green);
    renderText(renderer, fonts.font24, "1. Razarač (2X)",
               PLAYER_SHIPS_X, PLAYER_SHIPS_Y + SHIP_GAME_YADD * 4, green);

    SDL_Color red = {150, 50, 50, 255};

    renderText(renderer, fonts.font24, "5. Nosač Zrakoplova (5X)",
               ENEMY_SHIPS_X, ENEMY_SHIPS_Y, red);
    renderText(renderer, fonts.font24, "4. Bojni Brod (4X)",
               ENEMY_SHIPS_X, ENEMY_SHIPS_Y + SHIP_GAME_YADD, red);
    renderText(renderer, fonts.font24, "3. Krstarica (3X)",
               ENEMY_SHIPS_X, ENEMY_SHIPS_Y + SHIP_GAME_YADD * 2, red);
    renderText(renderer, fonts.font24, "2. Podmornica (3X)",
               ENEMY_SHIPS_X, ENEMY_SHIPS_Y + SHIP_GAME_YADD * 3, red);
    renderText(renderer, fonts.font24, "1. Razarač (2X)",
               ENEMY_SHIPS_X, ENEMY_SHIPS_Y + SHIP_GAME_YADD * 4, red);

    renderText(renderer, fonts.font28, "(17)",
               PLAYER_FLEET_X, PLAYER_FLEET_Y, green);
    renderText(renderer, fonts.font28, "(17)",
               ENEMY_FLEET_X, ENEMY_FLEET_Y, red);

    renderText(renderer, fonts.font28, "00:15",
               TIMER_GAME_X, TIMER_GAME_Y, red);

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
