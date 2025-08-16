#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "board.h"
#include "ship.h"
#include <vector>
#include <chrono>

struct GameState {
    bool serverResponsePending;
    bool inQueue;

    std::chrono::steady_clock::time_point setupStartTime;

    bool isPlayerTurn;
    Board* playerBoard;
    Board* enemyBoard;
    std::vector<Ship> playerShips;

    GameState();
    ~GameState();
};

#endif
