#include "game_state.h"

GameState::GameState()
           : serverResponsePending(false),
             inQueue(false),
             playerBoard(nullptr),
             enemyBoard(nullptr),
             playerShipSunk{},
             enemyShipSunk{} {}

GameState::~GameState() {
    delete playerBoard;
    delete enemyBoard;
}

GameState::isGameOver() const {
    return playerShipPoints == 0 || enemyShipPoints == 0;
}
