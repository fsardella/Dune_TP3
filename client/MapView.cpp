#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include "MapView.h"
#include "Camera.h"

#define TILESAMOUNT 40

MapView::MapView(SdlWindow& window)
: window(window),
  columns(0),
  rows(0) {
    this->loadTranslator();
}

void MapView::loadTranslator() {
    YAML::Node node = YAML::LoadFile("../tiles.yaml");
    for (int i = 0; i <= 0; i++) {
        std::vector<std::string> tileInfo = node[i].as<std::vector<std::string>>();
        tileInfoTranslator[i] = tileInfo;
    }
    for (int i = 0; i <= 0; i++) {
        std::string tileSizeKey(std::to_string(i) + " size");
        std::vector<int> tileSize = node[tileSizeKey].as< std::vector<int>>();
        tileSizeTranslator[i] = tileSize;
    }
}

void MapView::createMap(int height, int width, std::vector<std::vector<int>> map) {
    columns = width;
    rows = height;
    for (size_t i = 0; i < rows; i ++) {
        for(size_t j = 0; j < columns; j++) {
            std::vector<std::string> tileInfo = tileInfoTranslator[map[i][j]];
            std::vector<int> tileSize = tileSizeTranslator[map[i][j]];
            textureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(map[i][j]),
                          std::forward_as_tuple(tileInfo[1], window));
            auto& backgroundTexture = textureTranslator.at(map[i][j]);
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

void MapView::createUnit(int x, int y, std::string unitType, int unitId) {
    std::string path("../trike.bmp");
    unitTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(unitType),
                          std::forward_as_tuple(path, window, false));
    auto& unitTexture = unitTranslator.at(unitType);
    unitsTiles.emplace_back(unitTexture, 100, 100 , x, y, unitId);
}

MapView::~MapView() {
}

void MapView::render(Camera &cam) {
    for (BackGroundTile &tile : backgroundTiles) {
        cam.render(tile, 0);
    }
    for (Unit &unit : unitsTiles) {
        cam.render(unit, unit.getX(), unit.getY());
    }
}