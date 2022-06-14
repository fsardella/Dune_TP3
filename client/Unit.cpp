#include <iostream>
#include "Unit.h"
#include "Camera.h"

Unit::Unit(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY, int unitId)
: Renderizable(texture, sizeW, sizeH, posX, posY), id(unitId), propiety(true) {
    rescaling = 1;
}

void Unit::render(Camera &camera, size_t iteration) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSight(texture, src, posX, posY);
}

void Unit::render(Camera &camera, int posX, int posY) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForUnit(texture, src, posX, posY);
}

float Unit::getX() {
    return posX;
}

float Unit::getY() {
    return posY;
}

Unit::Unit(Unit &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}


Unit::~Unit() {
}
