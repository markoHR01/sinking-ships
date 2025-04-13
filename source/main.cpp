#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonts.h"
#include "scene.h"
#include "game_state.h"
#include "constants.h"

#include "menu.h"
#include "setup.h"
#include "game.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Potapanje Brodova",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    FontSet fonts;
    fonts.font86 = TTF_OpenFont("assets/fonts/OpenSans-ExtraBold.ttf", 86);
    fonts.font28 = TTF_OpenFont("assets/fonts/OpenSans-ExtraBold.ttf", 28);
    fonts.font24 = TTF_OpenFont("assets/fonts/OpenSans-ExtraBold.ttf", 24);

    GameState gameState;

    Scene currentScene = Scene::MainMenu;
    bool running = true;

    while(running) {
        switch (currentScene) {
            case Scene::MainMenu:
                currentScene = runMainMenu(renderer, fonts, gameState);
                break;
            case Scene::Setup:
                currentScene = runSetupScene(renderer, fonts, gameState);
                break;
            case Scene::Game:
                currentScene = runGameScene(renderer, fonts, gameState);
                break;
            case Scene::Quit:
                running = false;
                break;
        }
        SDL_Delay(16);
    }

    TTF_CloseFont(fonts.font86);
    TTF_CloseFont(fonts.font28);
    TTF_CloseFont(fonts.font24);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
