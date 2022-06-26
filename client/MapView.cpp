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
    this->loadFontTitles();
    this->loadTileTranslator();
    this->loadMenuTranslator();
    this->loadSpritesTranslator();
    this->createMenu();
}

void MapView::loadFontTitles() {
    TTF_Init();
    font = TTF_OpenFont("/usr/share/fonts/type1/urw-base35/URWBookman-Demi.t1", 22);
}

void MapView::loadSpritesTranslator() {
<<<<<<< HEAD
    YAML::Node node = YAML::LoadFile("../sprites.yaml");
=======
    YAML::Node node = YAML::LoadFile("../client/sprites.yaml");
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    int amount = node["amount"].as<int>();
    for (int i = 0; i < amount; i++) {
        std::map<std::tuple<int, int>, SdlTexture> animations;
        std::string animationAmountText(std::to_string(i) + "_animationAmount");
        int animationAmount = node[animationAmountText].as<int>();
        for(int j = 0; j < animationAmount; j++) {
            std::string animationIndex(std::to_string(i) + "_" + std::to_string(j));
            std::vector<std::string> spritesInfo = node[animationIndex].as<std::vector<std::string>>();
            for (size_t k = 0; k < spritesInfo.size(); k ++ ) {
                std::string path = spritesInfo[k];
                animations.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(std::make_tuple(j, k)),
                                    std::forward_as_tuple(path, &window, false));
            }
        }
        animationsRepository.insert({i, std::move(animations)});
    }
}

void MapView::loadTileTranslator() {
<<<<<<< HEAD
    YAML::Node node = YAML::LoadFile("../tiles.yaml");
=======
    YAML::Node node = YAML::LoadFile("../client/tiles.yaml");
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> tileInfo = node[i].as<std::vector<std::string>>();
        tileInfoTranslator[i] = tileInfo;

        tileTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(i),
                          std::forward_as_tuple(tileInfo[1], &window));
    }
}

void MapView::loadMenuTranslator() {
<<<<<<< HEAD
    YAML::Node node = YAML::LoadFile("../menu.yaml");
=======
    YAML::Node node = YAML::LoadFile("../client/menu.yaml");
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> menuImgInfo = node[i].as<std::vector<std::string>>();

        menuTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(i),
                          std::forward_as_tuple(menuImgInfo[1], &window));
    }
}

void MapView::createMenu() {
    for (size_t i = 0; i <= 18; i += 3) {
        for (size_t j = 0; j < 3; j++) {
            if (i == 0 && j == 0) {
                auto image = menuTextureTranslator.find(houseNumberClient);
                menuImages.emplace_back(&image->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, j, i);
                continue;
            }
            if (i == 18 && j > 0) continue;
            size_t row = i / 3;
            if (i == 0) row = i;
            auto image = menuTextureTranslator.find(i + 2 + j);
            menuImages.emplace_back(&image->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, j, row);
        }
    }
}

void MapView::createMap(int height, int width, std::vector<std::vector<uint8_t>> map) {
    columns = width;
    rows = height;
    for (size_t i = 0; i < rows; i ++) {
        for (size_t j = 0; j < columns; j++) {
            std::vector<std::string> tileInfo = tileInfoTranslator[map[i][j]];
            auto& backgroundTexture = tileTextureTranslator.at(map[i][j]);
            backgroundTiles.emplace_back(&backgroundTexture, TILE_PIX_SIZE, TILE_PIX_SIZE, j, i);
        }
    }
}

void MapView::createUnit(int x, int y, int unitType, int house, bool property, int animationId) {
    int posX = int(x / 32);
    int posY = int(y / 32);
<<<<<<< HEAD
    animationsRepository.at(0);
    unitsTiles.emplace_back(animationsRepository.at(unitType), 100, 100, posX, posY, property, house, animationId);
}
/*
void MapView::createUnit(int x, int y, int unitType, int unitId) {
    std::string path("../small_trike.bmp");
    unitTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(unitType),
                          std::forward_as_tuple(path, window, true));
    auto& unitTexture = unitTextureTranslator.at(unitType);
    unitsTiles.emplace_back(unitTexture, 64, 64, x, y, unitId);
}
*/
=======
    /* en una mejor implementacion cada unidad tiene un identificador unico
    y unitTiles es un mapa con clave id*/
    for (Unit& unit : unitsTiles) {
        if (unit.getX() == posX && unit.getY() == posY) return;
    }
    unitsTiles.emplace_back(animationsRepository.at(unitType), 100, 100, posX, posY, property, house, animationId);
}

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
void MapView::setMoney(int actualMoney) {
    std::string text("Money: $" + std::to_string(actualMoney));
    menuTextsTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple("money"),
                          std::forward_as_tuple(&window, font, text));
    menuTexts.emplace(std::piecewise_construct,
                          std::forward_as_tuple("money"),
                          std::forward_as_tuple(&menuTextsTranslator.at("money"), 200, 32, 0, 0));
}

void MapView::setEnergy(int actualEnergy) {
    std::string text("Energy: " + std::to_string(actualEnergy) + "%");
    menuTextsTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple("energy"),
                          std::forward_as_tuple(&window, font, text));
    menuTexts.emplace(std::piecewise_construct,
                          std::forward_as_tuple("energy"),
                          std::forward_as_tuple(&menuTextsTranslator.at("energy"), 200, 32, 0, 1));
}

void MapView::renderMenu(Camera &cam) {
    cam.renderMenuRect();

    if(menuTextsTranslator.size() == 2) {
        cam.render(menuTexts.at("money"));
        cam.render(menuTexts.at("energy"));
    }

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
        int surpasses = unit.render(cam, unit.getX(), unit.getY());
        if (surpasses) {
            renderMenu(cam);
        }
    }
}

void MapView::update(int delta) {
    for (Unit &unit : unitsTiles) {
        unit.update(delta);
    }
}

MapView::~MapView() {
}
