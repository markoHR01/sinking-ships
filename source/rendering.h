#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "client.h"

void renderText(SDL_Renderer* renderer,
                TTF_Font* font,
                const std::string& text,
                int x,
                int y,
                SDL_Color color);

void renderLoadingAnimation(SDL_Renderer* renderer,
                            int x,
                            int y,
                            int size,
                            int interval);

void renderBoard(SDL_Renderer* renderer,
                 TTF_Font* font,
                 int x,
                 int y,
                 const Board& board,
                 const int sectorSize);

#endif
