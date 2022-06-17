#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include "MapView.h"
#include "Camera.h"

#include <iostream>

MapView::MapView(SdlWindow& window)
: window(window),
  columns(0),
  rows(0) {
    this->loadTileTranslator();
    this->loadMenuTranslator();
}

void MapView::loadTileTranslator() {
    YAML::Node node = YAML::LoadFile("../tiles.yaml");
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> tileInfo = node[i].as<std::vector<std::string>>();
        tileInfoTranslator[i] = tileInfo;

        std::string tileSizeKey(std::to_string(i) + " size");
        std::vector<int> tileSize = node[tileSizeKey].as< std::vector<int>>();
        tileSizeTranslator[i] = tileSize;

        tileTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(i),
                          std::forward_as_tuple(tileInfo[1], window));
    }
}

void MapView::loadMenuTranslator() {
    YAML::Node node = YAML::LoadFile("../menu.yaml");
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> menuImgInfo = node[i].as<std::vector<std::string>>();

        menuTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(i),
                          std::forward_as_tuple(menuImgInfo[1], window));
    }
}

void MapView::createMap(int height, int width, std::vector<std::vector<int>> map) {
    columns = width;
    rows = height;
    for (size_t i = 0; i < rows; i ++) {
        for(size_t j = 0; j < columns; j++) {
            std::vector<std::string> tileInfo = tileInfoTranslator[map[i][j]];
            std::vector<int> tileSize = tileSizeTranslator[map[i][j]];
            auto& backgroundTexture = tileTextureTranslator.at(map[i][j]);
            backgroundTiles.emplace_back(backgroundTexture, tileSize[0]*4, tileSize[1]*4, j, i);
        }
    }
}

// void MapView::createUnit(int x, int y, int unitType, int unitId, int house, bool property) {
//     std::string path("../trike.bmp");
//     unitTranslator.emplace(std::piecewise_construct,
//                           std::forward_as_tuple(unitType),
//                           std::forward_as_tuple(path, window, false));
//     auto& unitTexture = unitTranslator.at(unitType);
//     unitsTiles.emplace_back(unitTexture, 100, 100 , x, y, unitId, property, house);
// }

void MapView::createUnit(int x, int y, int unitType, int unitId) {
    std::string path("../small_trike.bmp");
    unitTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(unitType),
                          std::forward_as_tuple(path, window, true));
    auto& unitTexture = unitTextureTranslator.at(unitType);
    unitsTiles.emplace_back(unitTexture, 32, 32, x, y, unitId);
}

MapView::~MapView() {
}

void MapView::render(Camera &cam) {
    for (BackGroundTile &tile : backgroundTiles) {
        cam.render(tile);
    }
    for (Unit &unit : unitsTiles) {
        cam.render(unit, unit.getX(), unit.getY());
    }
}
