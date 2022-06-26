#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SdlTexture.h"
#include <map>
<<<<<<< HEAD
// #include <tuple>
#include <vector>

#define FRAME_DURATION 10000

class Animation {
    // std::map<std::tuple<int, int>, SdlTexture>& animationsRepository; //cada animacion tiene su ID
=======
#include <vector>

#define FRAME_DURATION 500

class Animation {
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    std::vector<SdlTexture*> frames;
    int currentAnimation;
    int currentTime;
    int animationTime;
    public:
    explicit Animation(std::vector<SdlTexture*> frames);
    SdlTexture* getTexture();
    void update(int delta);

    Animation(const Animation& other) = delete;
    Animation& operator=(const Animation& other) = delete;

    Animation(Animation&& other);
    Animation& operator=(Animation&& other);

    ~Animation();
};

#endif