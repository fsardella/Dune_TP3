#ifndef __UNIT_H__
#define __UNIT_H__

#include "Animation.h"
#include "Camera.h"

class Unit {
    std::vector<Animation> animations;
    std::map<std::tuple<int, int>, SdlTexture>& animationsRepository;
    std::map<int, SdlTexture>&  lifeTextures;
    std::vector<SdlTexture*> attackTextures;
    Animation attackAnimation;
    int sizeW;
    int sizeH;
    float posX;
    float posY;
    bool propiety;
    int unitType;
    int playerId;
    int animationId;
    int lifeId;
    bool isCurrentlyAttacking;
    bool isDead;
    SdlTexture* texture;
    SdlTexture* currentLifeTexture;

    public:
    Unit(std::map<std::tuple<int, int>, SdlTexture> &newAnimationsRepository,
         std::map<int, SdlTexture>&  lifeTextures,
         std::vector<SdlTexture*> attackTextures,
         int sizeW,
         int sizeH,
         float posX,
         float posY,
         bool propiety,
         int unitType,
         int playerId,
         int newAnimationId);

    int render(Camera &camera, float posX, float posY);

    Unit(const Unit& other) = delete;
    Unit& operator=(const Unit& other) = delete;

    Unit(Unit&& other);
    Unit& operator=(Unit&& other);

    void getTexture();
    void getLifeTexture();

    int findAnimationId(int animationType);
    void updateAnimationId(int oldAnimationId, int newAnimationId);
    float getX();
    float getY();
    int getWidth();
    int getHeight();
    
    bool getPropiety();
    int getAnimationId();
    void setAnimationId(int animationId);
    void setNewPosition(float x, float y);
    bool getIsDead();

    bool isAttacking();
    void startAttacking();
    void updateLife(int currentLife, int totalLife);

    void update(int delta);

    ~Unit();
};


#endif /*__UNIT_H__*/