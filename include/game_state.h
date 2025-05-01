#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "board.h"
#include "ship.h"
#include <vector>

struct GameState {
    bool inQueue;

    Board* playerBoard;
    std::vector<ShipPart> shipParts;
    std::vector<Ship> playerShips;

    GameState();
    ~GameState();
};

#endif
