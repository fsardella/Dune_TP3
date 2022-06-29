#include "Construction.h"

#include <iostream>

#define STILL_ANIMATION 0
#define CREATE_ANIMATION 1
#define DEAD_ANIMATION 2
#define LIFE_BAR_WIDTH 12 // hacer que sea mas grande?
#define LIFE_BAR_HEIGHT 4

Construction::Construction(std::map<std::tuple<int, int>, SdlTexture>& newAnimationsRepository,
                           std::map<int, SdlTexture>& lifeTextures,
                           int sizeW,
                           int sizeH,
                           float posX,
                           float posY,
                           int constType,
                           bool propiety)
: animationsRepository(newAnimationsRepository),
  lifeTextures(lifeTextures),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  constType(constType),
  propiety(propiety),
  animationId(1),
  lifeId(4),
  isDead(false)
{
    int actualSprite = 0;
    std::vector<SdlTexture*> textures;
    for (const auto& [key, value] : animationsRepository) {
        if (std::get<0>(key) != actualSprite) {
            animations.emplace_back(textures);
            actualSprite = std::get<0>(key);
            textures.clear();
        }
        int animationType = std::get<0>(key);
        int animationSprite = std::get<1>(key);
        textures.push_back(&(animationsRepository.at(std::make_tuple(animationType, animationSprite))));
    }
    animations.emplace_back(std::move(textures));
    getTexture();
    getLifeTexture();
}

int Construction::render(Camera &camera, int posX, int posY) {
    if (isDead) return 0;
    Area srcLife(0, 0, LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT);
    camera.renderInSightForUnit(currentLifeTexture, srcLife, posX, posY - 0.2);
    Area src(0, 0, sizeW, sizeH);
    return camera.renderInSightForUnit(texture, src, posX, posY);
}

float Construction::getX() {
    return posX;
}

float Construction::getY() {
    return posY;
}

bool Construction::getPropiety() {
	return propiety;
}

int Construction::getConstType() {
    return constType;
}

void Construction::getTexture() {
    texture = animations.at(animationId).getTexture();
}

int Construction::getWidth() {
    return sizeW;
}

int Construction::getHeight() {
    return sizeH;
}

void Construction::getLifeTexture() {
    currentLifeTexture = &(lifeTextures.at(lifeId));
}

bool Construction::getIsDead() {
    return isDead;
}

void Construction::updateLife(int currentLife, int totalLife) {
    lifeId = int(currentLife / (totalLife / 4));
    if (lifeId == 0) lifeId = 1;
    getLifeTexture();
    if (currentLife == 0) {
        animationId = DEAD_ANIMATION;
    }
}

void Construction::update(int delta) {
    if (isDead) return;
    if (animationId == DEAD_ANIMATION && animations.at(animationId).isLastFrame()) {
        isDead = true;
        return;
    }
	if (animationId == STILL_ANIMATION) return;
    animations.at(animationId).update(delta);
    getTexture();
	if (animations.at(animationId).isLastFrame() && animationId == CREATE_ANIMATION) {
		animationId = STILL_ANIMATION;
	}
}

Construction::Construction(Construction &&other)
: animations(std::move(other.animations)),
  animationsRepository(other.animationsRepository),
  lifeTextures(other.lifeTextures),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  constType(other.constType),
  propiety(other.propiety),
  animationId(other.animationId),
  lifeId(other.lifeId),
  isDead(other.isDead),
  texture(other.texture),
  currentLifeTexture(other.currentLifeTexture) 
{}

Construction::~Construction() {
}
