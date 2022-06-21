#ifndef __UNIT_H__
#define __UNIT_H__

#include "Renderizable.h"
#include "Animation.h"

class Unit : public Renderizable{
    Animation animation;
    bool propiety;
    int house;
    int rescaling;

    public:
    /*Unit(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           int unitId);*/

    Unit(Animation animation,
            int sizeW,
            int sizeH,
            float posX,
            float posY,
            bool property,
            int house);

    void render(Camera &camera) override;
    int render(Camera &camera, int posX, int posY) override;

    Unit(const Unit& other) = delete;
    Unit& operator=(const Unit& other) = delete;

    Unit(Unit&& other);
    Unit& operator=(Unit&& other);

    float getX();

    float getY();

    void update(int delta);

    ~Unit() override;

};


#endif /*__UNIT_H__*/