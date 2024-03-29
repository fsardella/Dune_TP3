#ifndef __UNIT_H__
#define __UNIT_H__

#include <tuple>
#include <map>
#include <vector>
#include "Animation.h"
#include "Construction.h"
#include "Camera.h"

class Unit {
    std::vector<Animation> animations;
    std::map<std::tuple<int, int>, SdlTexture>& animationsRepository;
    std::map<int, SdlTexture>&  lifeTextures;
    std::vector<SdlTexture*> attackTextures;
    SdlTexture* identifierTexture;
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
    bool isDying;
    bool isTouched;
    float destinationX;
    float destinationY;
    float bulletPaseX;
    float bulletPaseY;
    bool reachedDestination;
    int misilIteration;
    int previosAnimationId;
    int currentAttackType;
    Unit* attackedUnit;
    Construction* attackedConstruction;
    SdlTexture* texture;
    SdlTexture* currentLifeTexture;

 public:
    Unit(std::map<std::tuple<int, int>, SdlTexture> &newAnimationsRepository,
         std::map<int, SdlTexture>&  lifeTextures,
         std::vector<SdlTexture*> attackTextures,
         SdlTexture* identifierTexture,
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
    void getIdentificatorTexture();

    void calculateBulletPosition(float& direcX, float& direcY, int animationId);
    void calculateMisilPosition(float& direcX, float& direcY, int animationId);
    void updateAnimationId(int oldAnimationId, int newAnimationId);
    float getX();
    float getY();
    int getWidth();
    int getHeight();

    int getPlayerId();
    void setPlayerId(int newPlayerId, SdlTexture* newIdentifier);
    void setPropiety(bool newPropiety);

    bool getPropiety();
    int getAnimationId();
    void setAnimationId(int animationId);
    void setNewPosition(float x, float y);
    bool getIsDead();
    bool getIsDying();
    void kill();
    int getUnitType();
    void setIsTouched(bool status);

    void setExplosion();

    int getAttackType();
    bool hasNoAttack();
    void setAttackType(int attackType, std::vector<SdlTexture*> attack);

    bool isAttacking();
    void startAttacking(float x, float y);
    void updateLife(int currentLife, int totalLife);
    void setMisilDestinationForUnit(float x, float y, Unit* attackedUnit);
    void setMisilDestinationForConstruction(float x, float y,
                                        Construction* attackedConstruction);
    void setSoundWaveDestination(float x, float y);
    void calculateSteps();

    void update(int delta);

    ~Unit();
};

#endif /*__UNIT_H__*/
