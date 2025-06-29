#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 720;

// Main Menu

const int TITLE_TOP_X = WINDOW_WIDTH / 2;
const int TITLE_TOP_Y = 120;
const int TITLE_BOTTOM_X = WINDOW_WIDTH / 2;
const int TITLE_BOTTOM_Y = 230;
const int BUTTON_X = (WINDOW_WIDTH - 220) / 2;
const int BUTTON_Y = 525;
const int BUTTON_W = 220;
const int BUTTON_H = 50;
const int LOAD_ANIMATION_X = (WINDOW_WIDTH - 90) / 2;
const int LOAD_ANIMATION_Y = BUTTON_Y - 100;
const int LOAD_SQUARE_SIZE = 10;
const int LOAD_INTERVAL = 500;

// Setup

const int BOARD_SIZE = 10;
const int SECTOR_SIZE = 35;
const int BOARD_SETUP_X = 78;
const int BOARD_SETUP_Y = 135;
const int SHIP_SETUP_X = 694;
const int SHIP_SETUP_Y = 190;
const int SHIP_SETUP_YADD = 55;
const int TIMER_SETUP_X = WINDOW_WIDTH / 2;
const int TIMER_SETUP_Y = 576;
const int DESTROYER_SIZE = 2;
const int SUBMARINE_SIZE = 3;
const int CRUISER_SIZE = 3;
const int BATTLESHIP_SIZE = 4;
const int AIRCRAFT_CARRIER_SIZE = 5;

const std::array<int, 5> SHIP_LIST = {
    DESTROYER_SIZE,
    SUBMARINE_SIZE,
    CRUISER_SIZE,
    BATTLESHIP_SIZE,
    AIRCRAFT_CARRIER_SIZE
};

// Game

const int PLAYER_BOARD_X = 50;
const int PLAYER_BOARD_Y = 50;
const int ENEMY_BOARD_X = 560;
const int ENEMY_BOARD_Y = 50;
const int PLAYER_SHIPS_X = 225;
const int PLAYER_SHIPS_Y = 450;
const int ENEMY_SHIPS_X = 735;
const int ENEMY_SHIPS_Y = 450;
const int SHIP_GAME_YADD = 45;
const int TIMER_GAME_X = 480;
const int TIMER_GAME_Y = 230;
const int PLAYER_FLEET_X = 480;
const int PLAYER_FLEET_Y = 130;
const int ENEMY_FLEET_X = 480;
const int ENEMY_FLEET_Y = 330;
const int EXIT_BUTTON_X = 405;
const int EXIT_BUTTON_Y = 540;
const int EXIT_BUTTON_W = 150;
const int EXIT_BUTTON_H = 50;

// NETWORK

constexpr const char* SERVER_HOST = "145.223.97.166";
const int SERVER_PORT = 22335;
const int CONNECT_TIMEOUT = 3000;
const int SOCKET_SELECT_TIMEOUT = 100;

#endif
