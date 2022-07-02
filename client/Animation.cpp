#include "Animation.h"
#include <utility>

#include <iostream>

/*
Pre: Constructor de la clase animación.
Post: Todos los atributos están inicializados. 
*/

Animation::Animation(std::vector<SdlTexture*> frames):
    frames(frames),
    currentAnimation(0),
    currentTime(0) {
    int animationSize = frames.size();
    animationTime = animationSize * FRAME_DURATION;
}

/*
Pre: Se setean las texturas para la animación requerida. 
Post: -
*/

void Animation::setTextures(std::vector<SdlTexture*> textures) {
    this->frames = textures;
    int animationSize = frames.size();
    animationTime = animationSize * FRAME_DURATION;
}

/*
Pre: Se obtienen las texturas para la animación requerida.
Post: -
*/

SdlTexture* Animation::getTexture() {
    if (currentAnimation < 0) currentAnimation = 0;
    return frames.at(currentAnimation);
}

/*
Pre: Se actualiza el frame para una animación.
Post: -
*/

void Animation::update(int delta) {
    animationTime = frames.size() * FRAME_DURATION;

    currentTime += delta;
    currentTime %= animationTime;
    currentAnimation = std::floor(currentTime / FRAME_DURATION);
}

/*
Pre: Se obtiene el frame actual de una animación.
Post: -
*/

int Animation::getFrame() {
    return currentAnimation;
}

/*
Pre: Se resetea la animación.
Post: -
*/

void Animation::reset() {
    currentAnimation = 0;
    currentTime = 0;
}

/*
Pre: Se chequea si es el último frame de una animación.
Post: -
*/

bool Animation::isLastFrame() {
    if (currentAnimation == static_cast<int>(frames.size()) - 1) return true;
    return false;
}

/*
Pre: Constuctor de la clase animación.
Post: -
*/

Animation::Animation(Animation &&other)
: frames(std::move(other.frames)),
currentAnimation(other.currentAnimation) {
}

/*
Pre: Destructor de la clase animación.
Post: -
*/

Animation::~Animation() {
}
