#include <iostream>
#include "Unit.h"
#include "Camera.h"
/*
Unit::Unit(SdlTexture &texture,
        int sizeW,
           int sizeH,
           float posX,
           float posY, int unitId)
: Renderizable(texture, sizeW, sizeH, posX, posY), id(unitId) {
    rescaling = 1;
}*/

Unit::Unit(Animation animation, 
            int sizeW,
            int sizeH,
            float posX,
            float posY, int unitId, bool property, int house)
: Renderizable(&animation.getTexture(), sizeW, sizeH, posX, posY), animation(std::move(animation)), id(unitId), propiety(true), house(house) {
    rescaling = 1;
}

void Unit::render(Camera &camera) {
}

int Unit::render(Camera &camera, int posX, int posY) {
    Area src(0, 0, sizeW, sizeH);
    return camera.renderInSightForUnit(texture, src, posX, posY);
}

float Unit::getX() {
    return posX;
}

float Unit::getY() {
    return posY;
}

void Unit::update(int delta) {
    animation.update(delta);
    setTexture(&animation.getTexture());
}

Unit::Unit(Unit &&other)
: Renderizable(std::move(other)),
  animation(std::move(other.animation)), 
  id(other.id),
  propiety(other.propiety),
  rescaling(other.rescaling) {
}

Unit::~Unit() {
}
