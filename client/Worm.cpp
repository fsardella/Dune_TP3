#include "Worm.h"
#include <utility>

#include <iostream>

Worm::Worm(std::vector<SdlTexture*> emptyTextures,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: attackAnimation(std::move(emptyTextures)),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  isCurrentlyAttacking(false) {
}

int Worm::render(Camera &camera, float posX, float posY) {
    Area src(0, 0, sizeW, sizeH);
    int i = camera.renderInSightForUnit(texture, src, posX, posY);
    return i;
}

float Worm::getX() {
    return posX;
}

float Worm::getY() {
    return posY;
}

int Worm::getWidth() {
    return sizeW;
}

int Worm::getHeight() {
    return sizeH;
}

void Worm::setNewPosition(float x, float y) {
    posX = x;
    posY = y;
}

void Worm::setTextures(std::vector<SdlTexture*> textures) {
    attackAnimation.setTextures(std::move(textures));
    getTexture();
}

void Worm::getTexture() {
    texture = attackAnimation.getTexture();
}

bool Worm::isAttacking() {
    return isCurrentlyAttacking;
}

void Worm::startAttacking() {
    isCurrentlyAttacking = true;
    attackAnimation.reset();
}

void Worm::update(int delta) {
    if (attackAnimation.isLastFrame()) {
        isCurrentlyAttacking = false;
        return;
    }
    attackAnimation.update(delta);
    getTexture();
}

Worm::Worm(Worm &&other)
: attackAnimation(std::move(other.attackAnimation)),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  isCurrentlyAttacking(other.isCurrentlyAttacking),
  texture(other.texture)
{}

Worm::~Worm() {
}
