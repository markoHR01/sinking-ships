#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonts.h"
#include "scene.h"
#include "game_state.h"

Scene runMainMenu(SDL_Renderer* renderer,
                  FontSet& fonts,
                  GameState& gameState);

#endif
