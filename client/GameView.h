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
    void buildMap(int height, int width, std::vector<std::vector<int>> map);
    void buildUnit(int x, int y, int unitType, int unitId);
    // void buildUnit(int x, int y, int unitType, int unitId, int house, bool property);
    // void buildUnits(std::map<int, std::tuple<int, int, int, bool>> units);
    void setSize(int newWidth, int newHeight);
    void shutdown();
    bool isRunning();
    void moveUpwards();
    void moveDownwards();
    void moveLeft();
    void moveRight();

    void setMoney(int actualMoney);
    void setEnergy(int actualEnergy);

    ~GameView();

};

#endif