#include "MenuImage.h"
#include "Camera.h"

#define BARRACK 18
#define LIGHT_FACTORY 12
#define HEAVY_FACTORY 13
#define PALACE 14

#include <iostream>

MenuImage::MenuImage(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           int type,
           SdlTexture* shadowTexture)
: Renderizable(texture, sizeW, sizeH, posX, posY),
  type(type),
  blocked(false),
  barracks(0),
  palaces(0),
  heavyFactorys(0),
  lightFactorys(0),
  isUnderConstruction(false),
  progress(0),
  shadowTexture(shadowTexture)
{
    if (type < 11) blocked = true;
    rescaling = 1;
}

void MenuImage::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForMenu(texture, src, posX, posY);
    if (isBlocked()) {
        camera.renderBlockingFigure(posX, posY);
    }
    if (isUnderConstruction) {
        Area shadowScr(0, 0, sizeW, sizeH - (sizeH * (float(progress) / float(100))));
        camera.renderShadowForMenu(shadowTexture, shadowScr, posX, posY, progress);
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
    if (type > 3 && type < 7 && heavyFactorys != 0 && palaces != 0) return true;
    if (type > 3 && type < 7 && palaces != 0 && heavyFactorys != 0) return true;
    if (type > 6 && type < 9 && barracks != 0) return true;
    if (type > 8 && type < 11 && barracks != 0 && palaces != 0) return true;
    if (type > 8 && type < 11 && palaces != 0 && barracks != 0) return true;
    return false;
}

void MenuImage::updateBuildings(int buildingType) {
    if (buildingType == BARRACK) barracks += 1;
    if (buildingType == HEAVY_FACTORY) heavyFactorys += 1;
    if (buildingType == PALACE) palaces += 1;
    if (buildingType == LIGHT_FACTORY) lightFactorys += 1;
}

void MenuImage::updateUnblocking(int buildingType) {
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
    if (progress == 100) isUnderConstruction = false;
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
  shadowTexture(other.shadowTexture)
{
}

MenuImage::~MenuImage() {
}
