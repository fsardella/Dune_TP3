#ifndef __UNIT_H__
#define __UNIT_H__

#include "Renderizable.h"

class Unit : public Renderizable{
    int rescaling;
    int id;
    // int house;
    // bool propiety;
    public:
    Unit(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           int unitId);

    // Unit(SdlTexture &texture,
    //        int sizeW,
    //        int sizeH,
    //        float posX,
    //        float posY,
    //        int unitId,
    //        bool property,
    //        int house);

    void render(Camera &camera) override;
    int render(Camera &camera, int posX, int posY) override;

    Unit(const Unit& other) = delete;
    Unit& operator=(const Unit& other) = delete;

    Unit(Unit&& other) ;
    Unit& operator=(Unit&& other) ;

    float getX();

    float getY();

    ~Unit() override;

};


#endif /*__UNIT_H__*/