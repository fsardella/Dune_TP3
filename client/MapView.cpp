#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include "MapView.h"
#include "Camera.h"

#include <iostream>

// #define CONSTRUCTION_OFFSET 11 antes esto estaba en el at de buildConstruction va?
#define UNIT_PIX_SIZE 12
#define BARRACK 18
#define PROGRESS_COMPLETED 100
#define HARKONNEN_SOUND_OFFSET 14
#define ATREIDES_SOUND_OFFSET 19
#define ORDOS_SOUND_OFFSET 24
#define UNIT_CREATED 4
#define UNIT_ATTACKED 29
#define BUILDING_CREATED 2
#define HOUSE_HARKONNEN 0
#define HOUSE_ATREIDES 1
#define HOUSE_ORDOS 2
#define CONSTRUCTION_YARD_ID 11
#define CONSTRUCTION_YARD_ATTACKED 3
#define WITHOUT_LIFE 0
#define EXPLOSION 11
#define MISIL_SOUND 13
#define GUN_SOUND 12

MapView::MapView(SdlWindow& window, int houseNumberClient)
: window(window),
  houseNumberClient(houseNumberClient),
  columns(0),
  rows(0)
  {
    this->loadFontTitles();
    this->loadTileTranslator();
    this->loadMenuTranslator();
    this->loadSpritesTranslator();
    this->loadLifeTranslator();
    this->loadAttackTranslator();
    this->loadIdentifierTranslator();
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

void MapView::loadIdentifierTranslator() {
    YAML::Node node = YAML::LoadFile("../client/ident.yaml");
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> identifierMgsInfo = node[i].as<std::vector<std::string>>();
        identifierTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(identifierMgsInfo[0],
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

void MapView::loadAttackTranslator() {
    YAML::Node node = YAML::LoadFile("../client/armament.yaml");
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        if (i == 3) continue;
        std::vector<std::string> attackInfo = node[i].as<std::vector<std::string>>();
        for (size_t j = 0; j < attackInfo.size(); j++) {
                attackTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(std::make_tuple(i, j)),
                                      std::forward_as_tuple(attackInfo[j],
                                      &window));
        }
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

void MapView::createUnit(int x, int y, int unitId, int unitType, int playerId, int animationId, bool propiety) {
    float posX = float(x) / float(TILE_PIX_SIZE);
    float posY = float(y) / float(TILE_PIX_SIZE);

    if (unitTiles.find(unitId) != unitTiles.end() &&
        unitTiles.at(unitId).getAnimationId() == animationId &&
        unitTiles.at(unitId).getX() == posX &&
        unitTiles.at(unitId).getY() == posY) {
            return;
    }
    if (unitTiles.find(unitId) != unitTiles.end()) {
        if (unitTiles.at(unitId).getAnimationId() != animationId) {
            unitTiles.at(unitId).setAnimationId(animationId);
        }
        if (unitTiles.at(unitId).getX() != posX ||
            unitTiles.at(unitId).getY() != posY) {
            unitTiles.at(unitId).setNewPosition(posX, posY);
        }
        return;
    }

    std::vector<SdlTexture*> attackSprites;
    for (int i = 0; i < 3; i ++) {
        attackSprites.push_back(&(attackTextureTranslator.at(std::make_tuple(unitType, i))));
    }

    unitTiles.emplace(std::piecewise_construct,
                       std::forward_as_tuple(unitId),
                       std::forward_as_tuple(animationsRepository.at(unitType),
                                             lifeTextureTranslator,
                                             std::move(attackSprites),
                                             &(identifierTranslator.at(playerId)),
                                             UNIT_PIX_SIZE, UNIT_PIX_SIZE,
                                             posX, posY, propiety, unitType,
                                             playerId, animationId));
}

void MapView::updateBlockedUnits(int constType) {
    for (MenuImage &image : menuImages) {
        image.updateUnblocking(constType);
    }
}

void MapView::updateUnblockedUnits(int constType) {
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

void MapView::createConstruction(int x, int y, int playerId, int constructionId,
                                 int constType, bool propiety, int house) {
    float posX = float(x) / float(TILE_PIX_SIZE);
    float posY = float(y) / float(TILE_PIX_SIZE);
    if (house != -1) {
        // hacer otra cuenta para obtener los textures
    }
    if (constType == BARRACK) {
        constType += house;
    }
    int width, height;
    getBuildingDimensions(constType, &width, &height);

    constructionTiles.emplace(std::piecewise_construct,
                    std::forward_as_tuple(constructionId),
                    std::forward_as_tuple(animationsRepository.at(constType),
                                          lifeTextureTranslator,
                                          &(identifierTranslator.at(playerId)),
                                          width, height, posX, posY,
                                          constType, playerId, propiety));
    updateBlockedUnits(constType);
}

void MapView::updateProgress(int menuId, int progress) {
    int soundCreationType = menuId > 10 ? BUILDING_CREATED : UNIT_CREATED;

    int offset = getSoundOffset();

    if(progress == PROGRESS_COMPLETED) {
        window.playSound(offset + soundCreationType, VOLUME);
    }
    menuImages.at(menuId).updateProgress(progress);
}

int MapView::getSoundOffset() {
    if(houseNumberClient == HOUSE_HARKONNEN) {
        return HARKONNEN_SOUND_OFFSET;
    }
    else if(houseNumberClient == HOUSE_ATREIDES) {
        return ATREIDES_SOUND_OFFSET;
    }
    else {
        return ORDOS_SOUND_OFFSET;
    }
}

void MapView::attackUnit(int attackerId, int attackedId, int currentLife, int totalLife) {
    if(unitTiles.at(attackedId).getPropiety()) {
        window.playSound(UNIT_ATTACKED, VOLUME);
    }

    unitTiles.at(attackerId).startAttacking();
    
    if((unitTiles.at(attackerId).getUnitType() == 4) || 
        ((unitTiles.at(attackerId).getUnitType() > 7) && 
        (unitTiles.at(attackerId).getUnitType() < 11))) {
        window.playSound(MISIL_SOUND, VOLUME);
    }
    else if((unitTiles.at(attackerId).getUnitType() == 0 || 
        (unitTiles.at(attackerId).getUnitType() == 7))) {
        window.playSound(GUN_SOUND, VOLUME);
    }

    unitTiles.at(attackedId).updateLife(currentLife, totalLife);
    if((currentLife == WITHOUT_LIFE) && (unitTiles.at(attackedId).getUnitType() > 6 
        && unitTiles.at(attackedId).getUnitType() < 11)) {
        window.playSound(EXPLOSION, VOLUME);
    }
}

void MapView::attackBuilding(int attackerId, int attackedId, int currentLife, int totalLife) {
    if((constructionTiles.at(attackedId).getConstType() == CONSTRUCTION_YARD_ID) && 
        (constructionTiles.at(attackedId).getPropiety())) {
        int offset = getSoundOffset();
        window.playSound(offset + CONSTRUCTION_YARD_ATTACKED, VOLUME);
    }
    unitTiles.at(attackerId).startAttacking();

    if((unitTiles.at(attackerId).getUnitType() == 4) || 
        ((unitTiles.at(attackerId).getUnitType() > 7) && 
        (unitTiles.at(attackerId).getUnitType() < 11))) {
        window.playSound(MISIL_SOUND, VOLUME);
    }
    else if((unitTiles.at(attackerId).getUnitType() == 0 || 
        (unitTiles.at(attackerId).getUnitType() == 7))) {
        window.playSound(GUN_SOUND, VOLUME);
    }

    if (currentLife == 0 && constructionTiles.at(attackedId).getPropiety()) {
        updateUnblockedUnits(constructionTiles.at(attackedId).getConstType());
    }
    constructionTiles.at(attackedId).updateLife(currentLife, totalLife);
    if(currentLife == WITHOUT_LIFE) {
        window.playSound(EXPLOSION, VOLUME);
    }
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
    for (auto const& unit : unitTiles) {
        if (unitTiles.at(unit.first).getIsDead()) continue;
        int surpasses = unitTiles.at(unit.first).render(cam,
                                            unitTiles.at(unit.first).getX(),
                                            unitTiles.at(unit.first).getY());
        if (surpasses) {
            renderMenu(cam);
        }    
    }
    for (auto const& building : constructionTiles) {
        if (constructionTiles.at(building.first).getIsDead()) continue;
        int surpasses = constructionTiles.at(building.first).render(cam,
                                constructionTiles.at(building.first).getX(),
                                constructionTiles.at(building.first).getY());
        if (surpasses) {
            renderMenu(cam);
        }    
    }
}

void MapView::update(int delta) {
    for (auto const& unit : unitTiles) {
        unitTiles.at(unit.first).update(delta);
    }
    for (auto const& building : constructionTiles) {
        constructionTiles.at(building.first).update(delta);
    }
}

int MapView::isBuilding(int posX, int posY, bool propiety) {
    for (auto const& building : constructionTiles) {
        if ((posX >= constructionTiles.at(building.first).getX() * TILE_PIX_SIZE &&
            (posX <= (constructionTiles.at(building.first).getX() * TILE_PIX_SIZE +
            constructionTiles.at(building.first).getWidth()))) &&
            (posY >= constructionTiles.at(building.first).getY() * TILE_PIX_SIZE &&
            (posY <= (constructionTiles.at(building.first).getY() * TILE_PIX_SIZE +
            constructionTiles.at(building.first).getHeight()))) &&
            constructionTiles.at(building.first).getPropiety() == propiety) {
                return building.first;
        }
    }
    return -1;
}
    
int MapView::isUnit(int posX, int posY, bool propiety) {
    for (auto const& unit : unitTiles) {
        if ((posX >= unitTiles.at(unit.first).getX() * TILE_PIX_SIZE &&
            (posX <= (unitTiles.at(unit.first).getX() * TILE_PIX_SIZE +
            unitTiles.at(unit.first).getWidth()))) &&
            (posY >= unitTiles.at(unit.first).getY() * TILE_PIX_SIZE &&
            (posY <= (unitTiles.at(unit.first).getY() * TILE_PIX_SIZE +
            unitTiles.at(unit.first).getHeight()))) &&
            unitTiles.at(unit.first).getPropiety() == propiety) {
            return unit.first;
        }
    }
    return -1;
}

bool MapView::isBlocked(int currentUnit) {
    return menuImages[currentUnit].isBlocked();
}

MapView::~MapView() {
}
