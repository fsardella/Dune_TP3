#include "Animation.h"

#include <iostream>

Animation::Animation(std::map<int, SdlTexture> &newAnimationsRepository): 
    animationsRepository(newAnimationsRepository),
    currentAnimation(0),
    currentTime(0)
{
    int animationSize = animationsRepository.size();
    animationTime = animationSize * FRAME_DURATION;
}

Animation::~Animation() {
}

SdlTexture& Animation::getTexture() {
    std::cout << currentTime << std::endl;
    return animationsRepository.at(currentAnimation);
}

void Animation::update(int delta) {
    animationTime = animationsRepository.size() * FRAME_DURATION;

    currentTime += delta;
    currentTime %= animationTime;
    currentAnimation = std::floor(currentTime / FRAME_DURATION);
}

Animation::Animation(Animation &&other)
: animationsRepository(other.animationsRepository),
currentAnimation(other.currentAnimation) {
}
