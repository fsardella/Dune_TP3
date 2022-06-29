#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>
#include <mutex>
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Renderizable.h"
#include "Camera.h"
#include "MapView.h"

class GameView {
    SdlWindow& window;
    Camera camera;
    MapView map;
    std::mutex gameViewMutex;
    bool running;
    public:
    GameView(SdlWindow& window, int houseNumberClient);

    GameView(const GameView& other) = delete;
    GameView& operator=(const GameView& other) = delete;

    GameView(GameView&& other) = delete;
    GameView& operator=(GameView&& other) = delete;

    void render();
    void buildMap(int height, int width, std::vector<std::vector<uint8_t>> map);
    void buildUnit(int x, int y, int unitId, int unitType, int playerId, int animationId, bool property);
    void buildUnits(std::map<int, std::tuple<int, int, int, int, int, bool>> units);
    void buildConstruction(int x, int y, int constructionId, int constType, bool property, int house);
    void setSize(int newWidth, int newHeight);
    void shutdown();
    bool isRunning();
    void moveUpwards();
    void moveDownwards();
    void moveLeft();
    void moveRight();
    
    void unitAttack(int attackerId, int attackedId, int currentLife, int totalLife);
    void buildingAttack(int attackerId, int attackedId, int currentLife, int totalLife);

    int getXOffset();
    int getYOffset();

    int isBuilding(int posX, int posY, bool propiety);
    int isUnit(int posX, int posY, bool propiety);

    bool isBlocked(int currentUnit);

    void setMoney(int actualMoney);
    void setEnergy(int actualEnergy);

    void update(int delta);

    ~GameView();

};

#endif