#include "GameView.h"
#include <cstdint>
#include <algorithm>
#include <iostream>
/*
GameView::GameView(SdlWindow& window, YAML::Node& clientConfiguration): 
  window(window),
  clientConfiguration(clientConfiguration),
  camera(window),
  map(window, clientConfiguration) {
}*/

GameView::GameView(SdlWindow& window): window(window), camera(window), map(window)  {
}

GameView::~GameView() {
}
/*
void GameView::buildMap(const std::string &mapString) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    try {
        map.loadMap(mapString);
    } catch (const std::exception& e) {
        shutdown();
    }
}*/

void GameView::buildMap(int height, int width, std::vector<std::vector<int>> mapMatrix) {
	map.createMap(height, width, mapMatrix);
}

// void GameView::buildUnit(int x, int y) {
//     std::lock_guard<std::mutex> lock(gameViewMutex);
//     try {
//         map.loadUnit(x,y);
//     } catch (const std::exception& e) {
//         shutdown();
//     }
// }

void GameView::render(size_t iteration) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.render(camera);
    window.render();
}

void GameView::shutdown() {
    SDL_Event quit;
    quit.type = SDL_QUIT;
    SDL_PushEvent(&quit);
}
