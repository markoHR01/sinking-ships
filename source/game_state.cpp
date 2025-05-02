#include "game_state.h"

GameState::GameState()
           : inQueue(false),
             playerBoard(nullptr),
             enemyBoard(nullptr) {}

GameState::~GameState() {
    delete playerBoard;
    delete enemyBoard;
}
