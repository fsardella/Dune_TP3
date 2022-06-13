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
    GameView(SdlWindow& window);

    GameView(const GameView& other) = delete;
    GameView& operator=(const GameView& other) = delete;

    GameView(GameView&& other) = delete;
    GameView& operator=(GameView&& other) = delete;

    void render();
    void buildMap(int height, int width, std::vector<std::vector<int>> map);
    void buildUnit(int x, int y, std::string unitType);
    void setSize(int newWidth, int newHeight);
    void shutdown();
    bool isRunning();
    ~GameView();

};

#endif