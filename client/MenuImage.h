#ifndef __MENUIMAGE_H__
#define __MENUIMAGE_H__

#include "Renderizable.h"

class MenuImage : public Renderizable {
    int type;
    int rescaling;
    bool blocked;
    bool hasBarrack;
    bool hasPalace;
    bool hasHeavyFactory;

    public:
    MenuImage(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY, 
           int type);

    void render(Camera &camera) override;
    
    MenuImage(const MenuImage& other) = delete;
    MenuImage& operator=(const MenuImage& other) = delete;

    MenuImage(MenuImage&& other);
    MenuImage& operator=(MenuImage&& other);

    int getX();
    int getY();

    bool isBlocked();
    bool checkUnblockPosibility(int buildingType);
    void updateBuildings(int buildingType);
    void updateBlocking(int buildingType);

    ~MenuImage();
};

#endif /*__MENUIMAGE_H__*/