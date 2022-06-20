#include "Animation.h"

Animation::Animation(std::map<int, SdlTexture> &newAnimationsRepository): 
    animationsRepository(newAnimationsRepository),
    currentAnimation(0)
{

}

Animation::~Animation() {
}

SdlTexture& Animation::getTexture() {
    return animationsRepository.at(currentAnimation);
}

Animation::Animation(Animation &&other)
: animationsRepository(other.animationsRepository),
currentAnimation(other.currentAnimation) {
}