#include "Construction.h"

#include <iostream>

#define STILL_ANIMATION 0
#define DEAD_ANIMATION 2

Construction::Construction(std::map<std::tuple<int, int>, SdlTexture>& newAnimationsRepository,
                           std::map<int, SdlTexture>& lifeTextures,
                           int sizeW,
                           int sizeH,
                           float posX,
                           float posY,
                           bool propiety)
: animationsRepository(newAnimationsRepository),
  lifeTextures(lifeTextures),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  propiety(propiety),
  animationId(1),
  lifeId(1),
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

int Construction::render(Camera &camera, int posX, int posY) {
    if (isDead) return 0;
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

void Construction::getTexture() {
    texture = animations.at(animationId).getTexture();
}

void Construction::getLifeTexture() {
    currentLifeTexture = &(lifeTextures.at(lifeId));
}

void Construction::updateLife(int currentLife, int totalLife) {
    lifeId = int(currentLife / (totalLife / 4));
    if (currentLife == 0) {
        animationId = 2;
    }
}

void Construction::update(int delta) {
    if (animationId == DEAD_ANIMATION && animations.at(animationId).isLastFrame()) isDead = true;
	if (animationId == STILL_ANIMATION) return;
    animations.at(animationId).update(delta);
    getTexture();
	if (animations.at(animationId).isLastFrame()) {
		animationId = 0;
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
  animationId(other.animationId),
  lifeId(other.lifeId),
  isDead(other.isDead),
  texture(other.texture),
  currentLifeTexture(other.currentLifeTexture) 
{}

Construction::~Construction() {
}
