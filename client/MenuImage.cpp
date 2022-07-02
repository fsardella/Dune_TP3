#include "MenuImage.h"
#include "Camera.h"
#include <utility>

#define BARRACK 18
#define LIGHT_FACTORY 12
#define HEAVY_FACTORY 13
#define PALACE 14

MenuImage::MenuImage(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           int type,
           std::vector<int>& houses)
: Renderizable(texture, sizeW, sizeH, posX, posY),
  type(type),
  blocked(false),
  barracks(0),
  palaces(0),
  heavyFactorys(0),
  lightFactorys(0),
  isUnderConstruction(false),
  progress(0),
  isReady(false),
  houses(houses) {
    if (type < 11) blocked = true;
    rescaling = 1;
}

void MenuImage::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForMenu(texture, src, posX, posY);
    if (blocked) {
        camera.renderBlockingFigure(posX, posY);
    }
    if (isUnderConstruction) {
        Area shadowScr(0, 0, sizeW, sizeH - (sizeH * (static_cast<float>
                       (progress) / static_cast<float>(100))));
        camera.renderShadowForMenu(shadowScr, posX, posY, progress);
    }
    if (isReady) {
        camera.renderReadyFigure(posX, posY);
    }
}

int MenuImage::getX() {
    return posX;
}

int MenuImage::getY() {
    return posY;
}

bool MenuImage::isBlocked() {
    return blocked;
}

bool MenuImage::checkUnblockPosibility(int buildingType) {
    if (type < 2 && lightFactorys != 0) return true;
    if (type > 2 && type < 4 && heavyFactorys != 0) return true;
    if (type > 3 && type < 7 && heavyFactorys != 0 && palaces != 0)
        return true;
    if (type > 3 && type < 7 && palaces != 0 && heavyFactorys != 0)
        return true;
    if (type > 6 && type < 9 && barracks != 0) return true;
    if (type > 8 && type < 11 && barracks != 0 && palaces != 0)
        return true;
    if (type > 8 && type < 11 && palaces != 0 && barracks != 0)
        return true;
    return false;
}

void MenuImage::updateBuildings(int buildingType) {
    if (buildingType == BARRACK) barracks += 1;
    if (buildingType == HEAVY_FACTORY) heavyFactorys += 1;
    if (buildingType == PALACE) palaces += 1;
    if (buildingType == LIGHT_FACTORY) lightFactorys += 1;
}

bool MenuImage::checkHouse(int house) {
    for (int& posibleHouse : houses) {
        if (posibleHouse == house) return true;
    }
    return false;
}

void MenuImage::updateUnblocking(int buildingType, int house) {
    if (!checkHouse(house)) return;
    updateBuildings(buildingType);
    if (checkUnblockPosibility(buildingType)) {
        blocked = false;
    }
}

void MenuImage::updateBlocking(int buildingType) {
    if (buildingType == BARRACK) barracks -= 1;
    if (buildingType == HEAVY_FACTORY) heavyFactorys -= 1;
    if (buildingType == PALACE) palaces -= 1;
    if (buildingType == LIGHT_FACTORY) lightFactorys -= 1;
    if (type < 11) {
        blocked = !checkUnblockPosibility(buildingType);
    }
}

void MenuImage::updateProgress(int progress) {
    if (!isUnderConstruction) {
        isUnderConstruction = true;
    }
    this->progress = progress;
    if (progress == 100) {
        if (type > 10) isReady = true;
        isUnderConstruction = false;
    }
}

bool MenuImage::isCurrentlyUnderConstruction() {
    return isUnderConstruction;
}

bool MenuImage::isBuildingReady() {
    return isReady;
}

void MenuImage::setNotReady() {
    isReady = false;
}

MenuImage::MenuImage(MenuImage &&other)
: Renderizable(std::move(other)),
  type(other.type),
  rescaling(other.rescaling),
  blocked(other.blocked),
  barracks(other.barracks),
  palaces(other.palaces),
  heavyFactorys(other.heavyFactorys),
  lightFactorys(other.lightFactorys),
  isUnderConstruction(other.isUnderConstruction),
  progress(other.progress),
  isReady(other.isReady),
  houses(other.houses) {
}

MenuImage::~MenuImage() {
}
