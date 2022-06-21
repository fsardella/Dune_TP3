#include "GameView.h"
#include <cstdint>
#include <algorithm>
#include <iostream>

GameView::GameView(SdlWindow& window, int houseNumberClient): window(window), camera(window), map(window, houseNumberClient), running(true) {
}

GameView::~GameView() {
}

void GameView::buildMap(int height, int width, std::vector<std::vector<uint8_t>> mapMatrix) {
    std::cout << height << std::endl;
    std::cout << width << std::endl;
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.setMapSize(width, height);
	map.createMap(height, width, std::move(mapMatrix));
}
/*
void GameView::buildUnit(int x, int y, int unitType, int unitId) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.createUnit(x, y, unitType, unitId);
}
*/
void GameView::buildUnit(int x, int y, int unitType, int unitId, int house, bool property, int animationId) {
    // std::lock_guard<std::mutex> lock(gameViewMutex);
    map.createUnit(x, y, unitType, unitId, house, property, animationId);
}

void GameView::buildUnits(std::map<int, std::tuple<int, int, int, bool>> units) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    for (const auto& [key, value] : units) {
        // ver como hacer lo de los ids
        // std::cout << "x " << std::get<0>(value) << std::endl; 
        // std::cout << "y " << std::get<1>(value) << std::endl;
        // std::cout << "type " << key << std::endl; 
        // std::cout << "id " << 1 << std::endl; 
        // std::cout << "house " << std::get<2>(value) << std::endl; 
        // std::cout << "bool " << std::get<3>(value) << std::endl; 
        // std::cout << "anim id " << 0 << std::endl;
        buildUnit(std::get<0>(value), std::get<1>(value), key, 1, std::get<2>(value), std::get<3>(value), 0);
    }
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
	return running;
}

void GameView::shutdown() {
	running = false;
    SDL_Event quit;
    quit.type = SDL_QUIT;
    SDL_PushEvent(&quit);
}

void GameView::moveUpwards() {
    camera.moveUpwards();
}

void GameView::moveDownwards() {
    camera.moveDownwards();
}

void GameView::moveLeft() {
    camera.moveLeft();
}

void GameView::moveRight() {
    camera.moveRight();
}

void GameView::setMoney(int actualMoney) {
    map.setMoney(actualMoney);
}

void GameView::setEnergy(int actualEnergy) {
    map.setEnergy(actualEnergy);
}

void GameView::update(int delta) {
    map.update(delta);
}
