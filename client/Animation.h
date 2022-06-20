#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SdlTexture.h"
#include <map>

class Animation {
    std::map<int, SdlTexture> &animationsRepository; //cada animacion tiene su ID
    int currentAnimation;
    public:
    explicit Animation(std::map<int, SdlTexture> &newAnimationsRepository);
    SdlTexture& getTexture();

    Animation(const Animation& other) = delete;
    Animation& operator=(const Animation& other) = delete;

    Animation(Animation&& other);
    Animation& operator=(Animation&& other);

    ~Animation();
};

#endif