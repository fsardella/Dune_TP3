#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include "MapView.h"
#include "Camera.h"

#include <iostream>

MapView::MapView(SdlWindow& window, int houseNumberClient)
: window(window),
  houseNumberClient(houseNumberClient),
  columns(0),
  rows(0) {
    this->loadTileTranslator();
    this->loadMenuTranslator();
    this->createMenu();
}

void MapView::loadTileTranslator() {
    YAML::Node node = YAML::LoadFile("../tiles.yaml");
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> tileInfo = node[i].as<std::vector<std::string>>();
        tileInfoTranslator[i] = tileInfo;

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

void MapView::createMenu() {
    // esto aca queda feo
    auto constYard = menuTextureTranslator.find(3);
    menuImages.emplace_back(constYard->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, 1, 0);

    for (size_t i = 0; i <= 18; i += 3) {
        for (size_t j = 0; j < 3; j++) {
            if (i == 0 && j == 0) {
                // REEMPLAZAR
                // auto barrack = menuTextureTranslator.find(houseNumberClient);
                auto image = menuTextureTranslator.find(i);
                menuImages.emplace_back(image->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, j, i);
                continue;
            }
            if (i == 18 && j > 0) continue;
            size_t row = i / 3;
            if (i == 0) row = i;
            auto image = menuTextureTranslator.find(i + 2 + j);
            menuImages.emplace_back(image->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, j, row);
        }
    }
}

void MapView::createMap(int height, int width, std::vector<std::vector<int>> map) {
    columns = width;
    rows = height;
    for (size_t i = 0; i < rows; i ++) {
        for (size_t j = 0; j < columns; j++) {
            std::vector<std::string> tileInfo = tileInfoTranslator[map[i][j]];
            auto& backgroundTexture = tileTextureTranslator.at(map[i][j]);
            backgroundTiles.emplace_back(backgroundTexture, TILE_PIX_SIZE, TILE_PIX_SIZE, j, i);
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
    unitsTiles.emplace_back(unitTexture, 64, 64, x, y, unitId);
}

MapView::~MapView() {
}

void MapView::renderMenu(Camera &cam) {
    cam.renderMenuRect();
    for (MenuImage &image : menuImages) {
        cam.render(image);
    }
}

void MapView::render(Camera &cam) {
    renderMenu(cam);
    for (BackGroundTile &tile : backgroundTiles) {
        cam.render(tile);
    }
    for (Unit &unit : unitsTiles) {
        int surpasses = cam.render(unit, unit.getX(), unit.getY());
        if (surpasses) {
            renderMenu(cam);
        }
    }
}
