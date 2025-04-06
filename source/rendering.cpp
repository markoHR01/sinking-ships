#include "rendering.h"

void renderText(SDL_Renderer* renderer,
                TTF_Font* font,
                const std::string& text,
                int x,
                int y,
                SDL_Color color) {
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textureBounds = {x - surface->w / 2, y - surface->h / 2,
                              surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &textureBounds);
    SDL_DestroyTexture(texture);
}

void renderLoadingAnimation(SDL_Renderer* renderer,
                            int x,
                            int y,
                            int size,
                            int interval) {
    Uint32 time = SDL_GetTicks() / interval;
    int step = time % 5;

    SDL_Rect square = {x + step * (size * 2), y, size, size};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &square);
}
