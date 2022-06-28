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
           int type)
: Renderizable(texture, sizeW, sizeH, posX, posY),
  type(type),
  blocked(false),
  hasBarrack(false),
  hasPalace(false),
  hasHeavyFactory(false)
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
    if (type < 2 && buildingType == LIGHT_FACTORY) return true;
    if (type > 2 && type < 4 && buildingType == HEAVY_FACTORY) return true;
    if (type > 3 && type < 7 && buildingType == HEAVY_FACTORY && hasPalace) return true;
    if (type > 3 && type < 7 && buildingType == PALACE && hasHeavyFactory) return true;
    if (type > 6 && type < 9 && buildingType == BARRACK) return true;
    if (type > 8 && type < 11 && buildingType == BARRACK && hasPalace) return true;
    if (type > 8 && type < 11 && buildingType == PALACE && hasBarrack) return true;
    return false;
}

void MenuImage::updateBuildings(int buildingType) {
    if (buildingType == BARRACK) hasBarrack = true;
    if (buildingType == HEAVY_FACTORY) hasHeavyFactory = true;
    if (buildingType == PALACE) hasPalace = true;
}

void MenuImage::updateBlocking(int buildingType) {
    std::cout << "me llamaron \n";
    if (checkUnblockPosibility(buildingType)) {
        blocked = false;
    }
    updateBuildings(buildingType);
}

MenuImage::MenuImage(MenuImage &&other)
: Renderizable(std::move(other)),
  type(other.type),
  rescaling(other.rescaling),
  blocked(other.blocked),
  hasBarrack(other.hasBarrack),
  hasPalace(other.hasPalace),
  hasHeavyFactory(other.hasHeavyFactory)
{
}

MenuImage::~MenuImage() {
}
