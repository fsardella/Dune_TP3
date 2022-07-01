#ifndef __MENUIMAGE_H__
#define __MENUIMAGE_H__

#include "Renderizable.h"

class MenuImage : public Renderizable {
    int type;
    int rescaling;
    bool blocked;
    int barracks;
    int palaces;
    int heavyFactorys;
    int lightFactorys;
    bool isUnderConstruction;
    int progress;
    bool isReady;
    std::vector<int>& houses;

    public:
    MenuImage(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY, 
           int type,
           std::vector<int>& houses);

    void render(Camera &camera) override;
    
    MenuImage(const MenuImage& other) = delete;
    MenuImage& operator=(const MenuImage& other) = delete;

    MenuImage(MenuImage&& other);
    MenuImage& operator=(MenuImage&& other);

    int getX();
    int getY();

    bool isBlocked();
    void updateUnblocking(int buildingType, int house);
    void updateBuildings(int buildingType);
    void updateBlocking(int buildingType);
    void updateUnblocking(int buildingType);
    bool checkUnblockPosibility(int buildingType);
    bool checkHouse(int house);

    void updateProgress(int progress);

    bool isCurrentlyUnderConstruction();
    bool isBuildingReady();
    void setNotReady();

    ~MenuImage();
};

#endif /*__MENUIMAGE_H__*/