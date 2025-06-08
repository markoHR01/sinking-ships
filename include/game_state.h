#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "board.h"
#include "ship.h"
#include <vector>

struct GameState {
    bool serverResponsePending;
    bool inQueue;

    Board* playerBoard;
    Board* enemyBoard;
    std::vector<Ship> playerShips;

    GameState();
    ~GameState();
};

#endif
