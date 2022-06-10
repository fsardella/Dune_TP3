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
    YAML::Node& clientConfiguration;
    Camera camera;
    MapView map;
    std::mutex gameViewMutex;
    public:
    GameView(SdlWindow& window, YAML::Node& clientConfiguration);

    GameView(const GameView& other) = delete;
    GameView& operator=(const GameView& other) = delete;

    GameView(GameView&& other) = delete;
    GameView& operator=(GameView&& other) = delete;

    void render(size_t iteration);
    void buildMap(const std::string &mapString);
    void buildUnit(int x, int y);
    void shutdown();
    ~GameView();

};

#endif