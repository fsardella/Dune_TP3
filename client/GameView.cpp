#include "GameView.h"
#include <cstdint>
#include <algorithm>
#include <iostream>

GameView::GameView(SdlWindow& window): window(window), camera(window), map(window), running(true) {
}

GameView::~GameView() {
}

void GameView::buildMap(int height, int width, std::vector<std::vector<int>> mapMatrix) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
	map.createMap(height, width, mapMatrix);
}

void GameView::buildUnit(int x, int y, std::string unitType) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.createUnit(x, y, unitType);
}

void GameView::render() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.render(camera);
    window.render();
}

void GameView::setSize(int newWidth, int newHeight) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
	this->window.setSize(newWidth, newHeight);
}

bool GameView::isRunning() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
	return running;
}

void GameView::shutdown() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
	running = false;
    SDL_Event quit;
    quit.type = SDL_QUIT;
    SDL_PushEvent(&quit);
}
