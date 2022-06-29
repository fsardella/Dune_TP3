#include "Animation.h"

#include <iostream>

Animation::Animation(std::vector<SdlTexture*> frames): 
    frames(frames),
    currentAnimation(0),
    currentTime(0)
{
    int animationSize = frames.size();
    animationTime = animationSize * FRAME_DURATION;
}

SdlTexture* Animation::getTexture() {
    if (currentAnimation < 0) currentAnimation = 0;
    return frames.at(currentAnimation);
}

void Animation::update(int delta) {
    animationTime = frames.size() * FRAME_DURATION;

    currentTime += delta;
    currentTime %= animationTime;
    currentAnimation = std::floor(currentTime / FRAME_DURATION);
}

int Animation::getFrame() {
    return currentAnimation;
}

void Animation::reset() {
    currentAnimation = 0;
    currentTime = 0;
}

bool Animation::isLastFrame() {
    if (currentAnimation == int(frames.size()) - 1) return true;
    return false;
}

Animation::Animation(Animation &&other)
: frames(std::move(other.frames)),
currentAnimation(other.currentAnimation) {
}

Animation::~Animation() {
}
