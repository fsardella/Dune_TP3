#include "GameView.h"
#include <cstdint>
#include <algorithm>
#include <iostream>

GameView::GameView(SdlWindow& window, int houseNumberClient)
: window(window), camera(window), map(window, houseNumberClient),
  running(true) {
}

GameView::~GameView() {
}

void GameView::buildMap(int height, int width, std::vector<std::vector<uint8_t>> mapMatrix) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.setMapSize(width, height);
	map.createMap(height, width, std::move(mapMatrix));
}

void GameView::buildUnit(int x, int y, int unitId, int unitType, int playerId, int animationId, bool property) {
    std::lock_guard<std::mutex> lock(gameViewMutex); // BORRAR
    map.createUnit(x, y, unitId, unitType, playerId, animationId, property);
}

void GameView::buildUnits(std::map<int, std::tuple<int, int, int, int, int, bool>> units) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    for (const auto& [key, value] : units) {
        buildUnit(std::get<0>(value), std::get<1>(value),
                  key, std::get<2>(value), std::get<3>(value),
                  std::get<4>(value), std::get<5>(value)); //segun un id de jugador podria tener un color identificador
    }
}

void GameView::buildConstruction(int x, int y, int playerId, int constructionId, int constType, bool property, int house) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.createConstruction(x, y, playerId, constructionId, constType, property, house);
}

void GameView::updateProgress(int menuId, int progress) {
    map.updateProgress(menuId, progress);
}

void GameView::unitAttack(int attackerId, int attackedId, int currentLife, int totalLife) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.attackUnit(attackerId, attackedId, currentLife, totalLife);
}

void GameView::buildingAttack(int attackerId, int attackedId, int currentLife, int totalLife) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.attackBuilding(attackerId, attackedId, currentLife, totalLife);
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

void GameView::moveUpwards() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveUpwards();
}

void GameView::moveDownwards() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveDownwards();
}

void GameView::moveLeft() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveLeft();
}

void GameView::moveRight() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveRight();
}

void GameView::setMoney(int actualMoney) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.setMoney(actualMoney);
}

void GameView::setEnergy(int actualEnergy) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.setEnergy(actualEnergy);
}

void GameView::update(int delta) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.update(delta);
}

int GameView::getXOffset() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return camera.getXOffset();
}

int GameView::getYOffset() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return camera.getYOffset();
}

int GameView::isBuilding(int posX, int posY, bool propiety) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBuilding(posX, posY, propiety);
}

int GameView::isUnit(int posX, int posY, bool propiety) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isUnit(posX, posY, propiety);
}

bool GameView::isBlocked(int currentUnit) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBlocked(currentUnit);
} 

bool GameView::isBuildingUnderConstruction(int currentBuilding) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBuildingUnderConstruction(currentBuilding);
}

bool GameView::isBuildingReady(int currentBuilding) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBuildingReady(currentBuilding);
}

void GameView::setNotReady(int currentBuilding) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.setNotReady(currentBuilding);
}

void GameView::destroyBuilding(int id) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.destroyBuilding(id);
}

void GameView::touchedUnit(int unitId) {
    map.touchedUnit(unitId);
}

void GameView::untouchedUnit(int unitId) {
    map.untouchedUnit(unitId);
}
