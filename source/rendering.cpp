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

void renderBoard(SDL_Renderer* renderer,
                 TTF_Font* font,
                 int x,
                 int y,
                 const Board& board,
                 const int sectorSize) {
    int boardSize = board.size();
    int sectorBorder = 1;
    int sectorFillSize = sectorSize - 2 * sectorBorder;

    int boardOutlineSize = boardSize * sectorSize + 2 * sectorBorder;
    SDL_Rect boardOutline = {x - sectorBorder,
                             y - sectorBorder,
                             boardOutlineSize,
                             boardOutlineSize};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &boardOutline);

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            int sectorX = x + col * sectorSize;
            int sectorY = y + row * sectorSize;

            SDL_Rect sectorFill = {sectorX + sectorBorder,
                                   sectorY + sectorBorder,
                                   sectorFillSize,
                                   sectorFillSize};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &sectorFill);

            Token token = board(col, row);
            if (token != Token::Empty) {
                std::string symbol;
                SDL_Color color;

                switch (token) {
                    case Token::Miss:
                        symbol = "+"; color = {255, 255, 255, 255}; break;
                    case Token::PlayerShip:
                        symbol = "X"; color = {50, 150, 50, 255}; break;
                    case Token::PlayerShipHit:
                        symbol = "X"; color = {50, 50, 150, 255}; break;
                    case Token::EnemyShip:
                        symbol = "X"; color = {150, 50, 50, 255}; break;
                    default: break;
                }

                if (!symbol.empty()) {
                    int tokenX = sectorX + sectorSize / 2;
                    int tokenY = sectorY + sectorSize / 2;
                    renderText(renderer, font, symbol, tokenX, tokenY, color);
                }
            }
        }
    }
}
