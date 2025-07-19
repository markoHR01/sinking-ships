#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonts.h"
#include "scene.h"
#include "game_state.h"
#include "socket_factory.h"
#include "network_thread.h"
#include "constants.h"

#include "menu.h"
#include "setup.h"
#include "game.h"

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>

int main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main();
}

#endif

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

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }
#endif

    Socket* socket = createSocket();
    if (!socket) {
        return 1;
    }

    if (!socket->connect(SERVER_HOST, SERVER_PORT)) {
        delete socket;
        return 1;
    }

    NetworkThread network(socket);
    network.start();

    Scene currentScene = Scene::MainMenu;
    bool running = true;

    while(running) {
        switch (currentScene) {
            case Scene::MainMenu:
                currentScene = runMainMenu(renderer, fonts, gameState, network);
                break;
            case Scene::Setup:
                currentScene = runSetupScene(renderer, fonts, gameState, network);
                break;
            case Scene::Game:
                currentScene = runGameScene(renderer, fonts, gameState, network);
                break;
            case Scene::Quit:
                running = false;
                break;
        }
        SDL_Delay(16);
    }

    network.stop();
    delete socket;

#ifdef _WIN32
    WSACleanup();
#endif

    TTF_CloseFont(fonts.font86);
    TTF_CloseFont(fonts.font28);
    TTF_CloseFont(fonts.font24);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
