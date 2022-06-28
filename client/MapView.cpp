#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include "MapView.h"
#include "Camera.h"

#include <iostream>

#define CONSTRUCTION_OFFSET 11
#define UNIT_PIX_SIZE 12

MapView::MapView(SdlWindow& window, int houseNumberClient)
: window(window),
  houseNumberClient(houseNumberClient),
  columns(0),
  rows(0) {
    this->loadFontTitles();
    this->loadTileTranslator();
    this->loadMenuTranslator();
    this->loadSpritesTranslator();
    this->loadLifeTranslator();
    this->createMenu();
}

void MapView::loadFontTitles() {
    TTF_Init();
    font = TTF_OpenFont("/usr/share/fonts/type1/urw-base35/URWBookman-Demi.t1", 22);
}

void MapView::loadSpritesTranslator() {
    YAML::Node node = YAML::LoadFile("../client/sprites.yaml");
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
                                    std::forward_as_tuple(path, &window, 0, 0, 0));
            }
        }
        animationsRepository.insert({i, std::move(animations)});
    }
}

void MapView::loadTileTranslator() {
    YAML::Node node = YAML::LoadFile("../client/tiles.yaml");
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
    YAML::Node node = YAML::LoadFile("../client/menu.yaml");
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> menuImgInfo = node[i].as<std::vector<std::string>>();

        menuTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(menuImgInfo[1],
                                      &window));
    }
}

void MapView::loadLifeTranslator() {
    for (int i = 1; i <= 4; i ++) {
        std::string path("../client/animations/vida" + std::to_string(i) + ".bmp");
        lifeTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(path,
                                      &window));
    }
}

void MapView::createMenu() {
    for (size_t i = 0; i <= 18; i += 3) {
        for (size_t j = 0; j < 3; j++) {
            size_t row = i / 3;
            if (i == 18 && j == 0) {
                auto image = menuTextureTranslator.find(houseNumberClient + 18);
                menuImages.emplace_back(&image->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, j, row, 18);
                continue;
            }
            if (i == 18 && j > 0) continue;
            if (i == 0) row = i;
            auto image = menuTextureTranslator.find(i + j);
            menuImages.emplace_back(&image->second, IMAGE_PIX_WIDTH, IMAGE_PIX_HEIGHT, j, row, i + j);
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

void MapView::createUnit(int x, int y, int unitId, int unitType, int playerId, int animationId, bool property) {
    int posX = int(x / TILE_PIX_SIZE);
    int posY = int(y / TILE_PIX_SIZE);

    if (unitTiles.find(unitId) != unitTiles.end() &&
        unitTiles.at(unitId).getAnimationId() == animationId) return;
    if (unitTiles.find(unitId) != unitTiles.end()) {
        unitTiles.at(unitId).setAnimationId(animationId);
        return;
    }
    unitTiles.emplace(std::piecewise_construct,
                       std::forward_as_tuple(unitId),
                       std::forward_as_tuple(animationsRepository.at(unitType),
                                             lifeTextureTranslator,
                                             UNIT_PIX_SIZE, UNIT_PIX_SIZE,
                                             posX, posY, property, unitType,
                                             playerId, animationId));
}

void MapView::updateBlockedUnits(int constType) {
    for (MenuImage &image : menuImages) {
        image.updateBlocking(constType);
    }
}

void MapView::getBuildingDimensions(int constType, int* width, int* height) {
    if (constType == 13) {
        *width = 4 * TILE_PIX_SIZE;
        *height = 4 * TILE_PIX_SIZE;
        return;
    }
    if (constType == 16) {
        *width = TILE_PIX_SIZE;
        *height = TILE_PIX_SIZE;
        return;
    }
    if (constType == 18) {
        *width = 2 * TILE_PIX_SIZE;
        *height = 3 * TILE_PIX_SIZE;
        return;
    }
    *width = 3 * TILE_PIX_SIZE;
    *height = 3 * TILE_PIX_SIZE;
}

void MapView::createConstruction(int x, int y, int constructionId,
                                 int constType, bool property, int house) {
    int posX = int(x / TILE_PIX_SIZE);
    int posY = int(y / TILE_PIX_SIZE);
    if (house != -1) {
        // hacer otra cuenta para obtener los textures
    }
    int width, height;
    getBuildingDimensions(constType, &width, &height);

    constructionTiles.emplace(std::piecewise_construct,
                    std::forward_as_tuple(constructionId),
                    std::forward_as_tuple(animationsRepository.at(
                                          constType + CONSTRUCTION_OFFSET),
                                          lifeTextureTranslator,
                                          width, height, posX, posY,
                                          property));
    updateBlockedUnits(constType);
}

void MapView::attackUnit(int attackerId, int attackedId, int currentLife, int totalLife) {
    if (unitTiles.at(attackerId).isAttacking() && currentLife == 0) {
        unitTiles.at(attackerId).stopAttacking();
    }
    unitTiles.at(attackerId).startAttacking();
    unitTiles.at(attackedId).updateLife(currentLife, totalLife);
}

void MapView::attackBuilding(int attackerId, int attackedId, int currentLife, int totalLife) {
    if (unitTiles.at(attackerId).isAttacking() && currentLife == 0) {
        unitTiles.at(attackerId).stopAttacking();    
    }
    unitTiles.at(attackerId).startAttacking();
    constructionTiles.at(attackedId).updateLife(currentLife, totalLife);
}

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

    if (menuTextsTranslator.size() == 2) {
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
    for (size_t i = 0; i < unitTiles.size(); i ++) {
        int surpasses = unitTiles.at(i).render(cam, unitTiles.at(i).getX(), unitTiles.at(i).getY());
        if (surpasses) {
            renderMenu(cam);
        }
    }
}

void MapView::update(int delta) {
    for (size_t i = 0; i < unitTiles.size(); i ++) {
        unitTiles.at(i).update(delta);
    }
}

bool MapView::isBuilding(int posX, int posY, bool propiety) {
    for (size_t i = 0; i < constructionTiles.size(); i ++) {
        if (int(constructionTiles.at(i).getX()) == posX &&
            int(constructionTiles.at(i).getY()) == posY &&
            constructionTiles.at(i).getPropiety() == propiety) {
                return true;
        }
    }
    return false;
}
    
bool MapView::isUnit(int posX, int posY, bool propiety) {
    for (size_t i = 0; i < unitTiles.size(); i ++) {
        if (int(unitTiles.at(i).getX()) == posX &&
            int(unitTiles.at(i).getY()) == posY &&
            unitTiles.at(i).getPropiety() == propiety) {
                return true;
        }
    }
    return false;
}

bool MapView::isBlocked(int currentUnit) {
    return menuImages[currentUnit].isBlocked();
}

MapView::~MapView() {
}
