#include "Animation.h"
#include <utility>

/*
Pre: Constructor de la clase animación.
Post: Todos los atributos están inicializados. 
*/

Animation::Animation(std::vector<SdlTexture*> frames):
    frames(frames),
    currentAnimation(0),
    currentTime(0),
    frameDuration(FRAME_DURATION) {
    int animationSize = frames.size();
    animationTime = animationSize * frameDuration;
}

/*
Pre: Se setean las texturas para la animación requerida. 
Post: -
*/

void Animation::setTextures(std::vector<SdlTexture*> textures) {
    this->frames = textures;
    int animationSize = frames.size();
    animationTime = animationSize * frameDuration;
}

/*
Pre: Se setea una duración de frame. 
Post: -
*/

void Animation::setFrameDuration(int duration) {
    this->frameDuration = duration;
    int animationSize = this->frames.size();
    animationTime = animationSize * frameDuration;
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
    animationTime = frames.size() * frameDuration;

    currentTime += delta;
    currentTime %= animationTime;
    currentAnimation = std::floor(currentTime / frameDuration);
}

/*
Pre: Se obtiene el frame actual de una animación.
Post: -
*/

int Animation::getFrame() {
    return currentAnimation;
}

/*
Pre: Se obtienen la cantidad de frames.
Post: -
*/

int Animation::getFramesSize() {
    return this->frames.size();
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
currentAnimation(other.currentAnimation),
currentTime(other.currentTime),
animationTime(other.animationTime),
frameDuration(other.frameDuration) {
}

/*
Pre: Destructor de la clase animación.
Post: -
*/

Animation::~Animation() {
}
