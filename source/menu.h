#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void renderMainMenu(SDL_Renderer* renderer,
                    TTF_Font* titleFont,
                    TTF_Font* buttonFont,
                    bool inQueue);

#endif
