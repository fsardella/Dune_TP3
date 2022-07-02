#include "GameView.h"
#include <cstdint>
#include <algorithm>
#include <utility>

#include <iostream>

/*
Pre-Condiciones: Constructor del GameView.
Post-Condiciones: -
*/

GameView::GameView(SdlWindow& window, int houseNumberClient)
: window(window), camera(window), map(window, houseNumberClient),
  running(true) {
}

/*
Pre-Condiciones: Construye el mapa.
Post-Condiciones: -
*/

void GameView::buildMap(int height, int width,
                        std::vector<std::vector<uint8_t>> mapMatrix) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.setMapSize(width, height);
    map.createMap(height, width, std::move(mapMatrix));
}

/*
Pre-Condiciones: Construye una unidad.
Post-Condiciones: -
*/

void GameView::buildUnit(int x, int y, int unitId, int unitType, int playerId,
                         int animationId, bool property) {
    std::lock_guard<std::mutex> lock(gameViewMutex);  // BORRAR
    map.createUnit(x, y, unitId, unitType, playerId, animationId, property);
}

/*
Pre-Condiciones: Construye multiples unidades.
Post-Condiciones: -
*/

void GameView::buildUnits(std::map<int, std::tuple<int, int, int, int, int,
                          bool>> units) {
    // std::lock_guard<std::mutex> lock(gameViewMutex); // PONER
    for (const auto& [key, value] : units) {
        buildUnit(std::get<0>(value), std::get<1>(value),
                  key, std::get<2>(value), std::get<3>(value),
                  std::get<4>(value), std::get<5>(value));
    }
}

/*
Pre-Condiciones: Construye un edificio.
Post-Condiciones: -
*/

void GameView::buildConstruction(int x, int y, int playerId,
                                 int constructionId, int constType,
                                 bool property, int house) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.createConstruction(x, y, playerId, constructionId, constType, property,
                           house);
}

/*
Pre-Condiciones: Actualiza el progreso de una unidad o edificio en construcción.
Post-Condiciones: -
*/

void GameView::updateProgress(int menuId, int progress) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.updateProgress(menuId, progress);
}

/*
Pre-Condiciones: Determina el ataque de una unidad.
Post-Condiciones: -
*/

void GameView::unitAttack(int attackerId, int attackedId, int currentLife,
                          int totalLife) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.attackUnit(attackerId, attackedId, currentLife, totalLife);
}

/*
Pre-Condiciones: Determina el ataque a un edificio.
Post-Condiciones: -
*/

void GameView::buildingAttack(int attackerId, int attackedId, int currentLife,
                              int totalLife) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.attackBuilding(attackerId, attackedId, currentLife, totalLife);
}

/*
Pre-Condiciones: Renderiza la vista del juego.
Post-Condiciones: -
*/

void GameView::render() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.render(camera);
    window.render();
}

/*
Pre-Condiciones: Determina el tamanio de la ventana del juego.
Post-Condiciones: -
*/

void GameView::setSize(int newWidth, int newHeight) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    this->window.setSize(newWidth, newHeight);
}

/*
Pre-Condiciones: Devuelve true si el juego esta corriendo
o false si no. 
Post-Condiciones: -
*/

bool GameView::isRunning() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return running;
}

/*
Pre-Condiciones: Finaliza el juego.
Post-Condiciones: -
*/

void GameView::shutdown() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    running = false;
    SDL_Event quit;
    quit.type = SDL_QUIT;
    SDL_PushEvent(&quit);
}

/*
Pre-Condiciones: -
Post-Condiciones: La vista del juego se mueve para arriba.
*/

void GameView::moveUpwards() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveUpwards();
}

/*
Pre-Condiciones: -
Post-Condiciones: La vista del juego se mueve para abajo.
*/

void GameView::moveDownwards() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveDownwards();
}

/*
Pre-Condiciones: -
Post-Condiciones: La vista del juego se mueve para la izquierda.
*/

void GameView::moveLeft() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveLeft();
}

/*
Pre-Condiciones: -
Post-Condiciones: La vista del juego se mueve para la derecha.
*/

void GameView::moveRight() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    camera.moveRight();
}

/*
Pre-Condiciones: Setea el dinero del jugador.
Post-Condiciones: -
*/

void GameView::setMoney(int actualMoney) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.setMoney(actualMoney);
}

/*
Pre-Condiciones: Setea la energía del jugador.
Post-Condiciones: -
*/

void GameView::setEnergy(int actualEnergy) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.setEnergy(actualEnergy);
}

/*
Pre-Condiciones: Actualiza la vista del juego.
Post-Condiciones: -
*/

void GameView::update(int delta) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.update(delta);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el offset de x.
*/

int GameView::getXOffset() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return camera.getXOffset();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el offset de y.
*/

int GameView::getYOffset() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return camera.getYOffset();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si se clickeo
en un edificio o false si no. 
*/

int GameView::isBuilding(int posX, int posY, bool propiety) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBuilding(posX, posY, propiety);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si se clickeo
en una unidad o false si no. 
*/

int GameView::isUnit(int posX, int posY, bool propiety) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isUnit(posX, posY, propiety);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si la unidad esta bloqueada
o false si no.
*/

bool GameView::isBlocked(int currentUnit) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBlocked(currentUnit);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el edificio esta en construccion
o la unidad esta siendo entrenada o false si no. 
*/

bool GameView::isUnderConstruction(int current) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isUnderConstruction(current);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el edificio esta listo para 
ser posicionado.
*/

bool GameView::isBuildingReady(int currentBuilding) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    return map.isBuildingReady(currentBuilding);
}

/*
Pre-Condiciones: Setea que el edificio no esta construido todavia. 
Post-Condiciones: -
*/

void GameView::setNotReady(int currentBuilding) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.setNotReady(currentBuilding);
}

/*
Pre-Condiciones: Ataque de gusano de arena. 
Post-Condiciones: -
*/

void GameView::wormAttack(int x, int y, std::vector<int> deadId) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.wormAttack(x, y, deadId);
}

/*
Pre-Condiciones: Actualiza la especia según el estado de la misma.
Post-Condiciones: -
*/

void GameView::updateSpecie(int x, int y, int state) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.updateSpecie(x, y, state);
}

/*
Pre-Condiciones: Determina que el jugador toco a una unidad. 
Post-Condiciones: -
*/

void GameView::touchedUnit(int unitId) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.touchedUnit(unitId);
}

/*
Pre-Condiciones: La unidad tocada vuelve a su estado actual:
no tocada.
Post-Condiciones: -
*/

void GameView::untouchedUnit(int unitId) {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.untouchedUnit(unitId);
}

/*
Pre-Condiciones: Reproduce música en caso de que el jugador gane.
Post-Condiciones: -
*/

void GameView::playWinSound() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.playWinSound();
}

/*
Pre-Condiciones: Reproduce música en caso de que el jugador pierda.
Post-Condiciones: -
*/

void GameView::playLostSound() {
    std::lock_guard<std::mutex> lock(gameViewMutex);
    map.playLostSound();
}

/*
Pre-Condiciones: Destructor del GameView.
Post-Condiciones: -
*/

GameView::~GameView() {
}