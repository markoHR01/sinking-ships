#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "board.h"
#include "ship.h"
#include <vector>
#include <chrono>

struct GameState {
    bool serverResponsePending;
    bool inQueue;

    bool isPlayerTurn;

    Board* playerBoard;
    Board* enemyBoard;
    int playerShipPoints;
    int enemyShipPoints;

    std::vector<Ship> playerShips;
    std::chrono::steady_clock::time_point setupStartTime;
    std::chrono::steady_clock::time_point turnStartTime;

    GameState();
    ~GameState();
};

#endif
