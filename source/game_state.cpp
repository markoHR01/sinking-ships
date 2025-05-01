#include "game_state.h"

GameState::GameState()
           : inQueue(false),
             playerBoard(nullptr) {}

GameState::~GameState() {
    delete playerBoard;
}
