#include "Unit.h"

#include <iostream>

#define LIFE_BAR_WIDTH 12
#define LIFE_BAR_HEIGHT 4
#define VEHICLE_DEAD_ANIMATION 7
#define SOLDIER_DEAD_ANIMATION 5

Unit::Unit(std::map<std::tuple<int, int>, SdlTexture>& newAnimationsRepository,
           std::map<int, SdlTexture>&  lifeTextures,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           bool property,
           int unitType,
           int playerId,
           int animationId)
: animationsRepository(newAnimationsRepository),
  lifeTextures(lifeTextures),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  propiety(true),
  unitType(unitType),
  playerId(playerId),
  animationId(findAnimationId(animationId)),
  lifeId(4),
  isCurrentlyAttacking(false),
  isDead(false)
{
    int actualSprite = 0;
    std::vector<SdlTexture*> textures;
    for (const auto& [key, value] : animationsRepository) {
        if (std::get<0>(key) != actualSprite) {
            animations.emplace_back(textures);
            actualSprite = std::get<0>(key);
            std::vector<SdlTexture*> textures;
        }
        int animationType = std::get<0>(key);
        int animationSprite = std::get<1>(key);
        textures.push_back(&(animationsRepository.at(std::make_tuple(animationType, animationSprite))));
    }
    animations.emplace_back(textures);
    getTexture();
    getLifeTexture();
}

int Unit::findAnimationId(int animationType) {
    if (animationType >= 0 && animationType < 3) return 0;
    if (animationType == 3) return 1;
    if (animationType == 5) return 2;
    if (animationType >= 6 && animationType < 9) return 3;
    if (unitType < 7) {
        if (animationType == 4) return 2;
    }
    return 4;
}

void Unit::updateAnimationId(int oldAnimationId, int newAnimationId) {
    // solo si soy vehiculo
    if ((oldAnimationId == 2)) {
        if (newAnimationId >= 0 && newAnimationId < 3) animationId = 6;
        if (newAnimationId == 3) animationId = 5;
        if (newAnimationId >= 6 && newAnimationId < 9) animationId = 4;
    }
} 

int Unit::render(Camera &camera, int posX, int posY) {
    if (isDead) return 0;
    Area src(0, 0, sizeW, sizeH);
    if (isCurrentlyAttacking) {
        // dibujar destellos segun la direccion a donde mira (animationID)
    }
    Area srcLife(0, 0, LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT);
    camera.renderInSightForUnit(currentLifeTexture, srcLife, posX, posY - 0.2);
    return camera.renderInSightForUnit(texture, src, posX, posY);
}

float Unit::getX() {
    return posX;
}

float Unit::getY() {
    return posY;
}

bool Unit::getPropiety() {
    return propiety;
}

int Unit::getAnimationId() {
    return animationId;
}

void Unit::setAnimationId(int newAnimationId) {
    if (unitType < 7 && animationId == 2) {
        // si era vehiculo y estaba quieto, cualq direc es rotacion
        updateAnimationId(animationId, newAnimationId);
    } else {
        animationId = findAnimationId(newAnimationId);
    }
}

void Unit::getTexture() {
    texture = animations.at(animationId).getTexture();
}

void Unit::getLifeTexture() {
    currentLifeTexture = &(lifeTextures.at(lifeId));
}

bool Unit::isAttacking() {
    return isCurrentlyAttacking;
} 

void Unit::stopAttacking() {
    isCurrentlyAttacking = false;
}

void Unit::startAttacking() {
    isCurrentlyAttacking = true;
}

void Unit::updateLife(int currentLife, int totalLife) {
    lifeId = int(currentLife / (totalLife / 4));
    if (currentLife == 0) {
        if (unitType < 7) {
            animationId = VEHICLE_DEAD_ANIMATION;
        } else {
            animationId = SOLDIER_DEAD_ANIMATION;
        }
    
    }
}

void Unit::update(int delta) {
    if (unitType < 7 && animationId == VEHICLE_DEAD_ANIMATION
        && animations.at(animationId).isLastFrame()) isDead = true;
    if (unitType > 6 && animationId == SOLDIER_DEAD_ANIMATION
        && animations.at(animationId).isLastFrame()) isDead = true;
    if (unitType < 7 && !(animationId >= 4 && animationId < 7)) return; // quieto para vehiculo
    if (unitType > 6 && animationId == 4) return; // quieto para soldado
    animations.at(animationId).update(delta);
    getTexture();
    if (unitType < 7 && animations.at(animationId).isLastFrame()) { // soy vehiculo estoy en ultimo frame
		if (animationId == 4) {
            animationId = 3;
        } else if (animationId == 5) {
            animationId = 1;
        } else {
            animationId = 0;
        }
	}
}

Unit::Unit(Unit &&other)
: animations(std::move(other.animations)),
  animationsRepository(other.animationsRepository),
  lifeTextures(other.lifeTextures),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  propiety(other.propiety),
  unitType(other.unitType),
  playerId(other.playerId),
  animationId(other.animationId),
  lifeId(other.lifeId),
  texture(other.texture),
  currentLifeTexture(other.currentLifeTexture) {
}

Unit::~Unit() {
}
