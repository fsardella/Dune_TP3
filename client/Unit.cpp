#include <iostream>
#include "Unit.h"

#define FRAMES_AMOUNT 5

Unit::Unit(std::map<std::tuple<int, int>, SdlTexture>& newAnimationsRepository, 
            int sizeW,
            int sizeH,
            float posX,
            float posY,
            bool property,
            int house,
            int animationId)
: animationsRepository(newAnimationsRepository), 
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  propiety(true),
  house(house),
  animationId(animationId) 
{
    for (size_t i = 0; i < newAnimationsRepository.size() / 5; i ++) {
        std::vector<SdlTexture*> textures;
        for (int j = 0; j < FRAMES_AMOUNT; j ++) {
            textures.push_back(&(animationsRepository.at(std::make_tuple(i, j))));
        }
        animations.emplace_back(textures);
    }
    getTexture();
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

void Unit::getTexture() {
    texture = animations.at(animationId).getTexture();
}

void Unit::update(int delta) {
    animations.at(animationId).update(delta);
    getTexture();
}

Unit::Unit(Unit &&other)
: animations(std::move(other.animations)),
  animationsRepository(other.animationsRepository),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  propiety(other.propiety),
  house(other.house),
  animationId(other.animationId),
  texture(other.texture) {
}

Unit::~Unit() {
}
