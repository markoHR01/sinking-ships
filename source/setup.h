#ifndef SETUP_H
#define SETUP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonts.h"
#include "scene.h"
#include "game_state.h"

Scene runSetupScene(SDL_Renderer* renderer,
                    FontSet& fonts,
                    GameState& gameState);

#endif
