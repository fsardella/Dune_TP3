#include <iostream>
#include "NonMovable.h"
#include "Camera.h"

NonMovable::NonMovable(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: Renderizable(texture, sizeW, sizeH, posX, posY) {
    rescaling = 1;
}

void NonMovable::render(Camera &camera, size_t iteration) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSight(texture, src, posX, posY);
}

void NonMovable::render(Camera &camera, int posX, int posY) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForUnit(texture, src, posX, posY);
}

float NonMovable::getX() {
    return posX;
}

float NonMovable::getY() {
    return posY;
}

NonMovable::NonMovable(NonMovable &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}


NonMovable::~NonMovable() {
}