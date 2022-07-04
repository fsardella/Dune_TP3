#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SdlTexture.h"
#include <map>
#include <vector>
#define FRAME_DURATION 1000

class Animation {
    std::vector<SdlTexture*> frames;
    int currentAnimation;
    int currentTime;
    int animationTime;
    // int frameDuration;

 public:
    explicit Animation(std::vector<SdlTexture*> frames);
    SdlTexture* getTexture();
    void update(int delta);
    bool isLastFrame();
    int getFrame();
    void reset();

    void setTextures(std::vector<SdlTexture*> textures);

    Animation(const Animation& other) = delete;
    Animation& operator=(const Animation& other) = delete;

    Animation(Animation&& other);
    Animation& operator=(Animation&& other);

    ~Animation();
};

#endif /*__ANIMATION_H__*/
