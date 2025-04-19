#include "game.h"
#include "client.h"
#include "rendering.h"
#include "constants.h"

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

    Board playerBoard(BOARD_SIZE);
    Board enemyBoard(BOARD_SIZE);

    renderBoard(renderer, fonts.font28,
                PLAYER_BOARD_X, PLAYER_BOARD_Y, playerBoard, SECTOR_SIZE);
    renderBoard(renderer, fonts.font28,
                ENEMY_BOARD_X, ENEMY_BOARD_Y, enemyBoard, SECTOR_SIZE);

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
