#ifndef __UNIT_H__
#define __UNIT_H__

#include "Animation.h"
#include "Camera.h"

class Unit {
    std::vector<Animation> animations;
    std::map<std::tuple<int, int>, SdlTexture>& animationsRepository;
    int sizeW;
    int sizeH;
    float posX;
    float posY;
    bool propiety;
    int house;
    int animationId;
    SdlTexture* texture;

    public:
<<<<<<< HEAD
    /*Unit(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           int unitId);*/

=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    Unit(std::map<std::tuple<int, int>, SdlTexture> &newAnimationsRepository,
            int sizeW,
            int sizeH,
            float posX,
            float posY,
            bool property,
            int house,
            int animationId);

    int render(Camera &camera, int posX, int posY);

    Unit(const Unit& other) = delete;
    Unit& operator=(const Unit& other) = delete;

    Unit(Unit&& other);
    Unit& operator=(Unit&& other);

    void getTexture();

    float getX();

    float getY();

    void update(int delta);

    ~Unit();
};


#endif /*__UNIT_H__*/