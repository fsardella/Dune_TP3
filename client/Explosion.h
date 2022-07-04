#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "Animation.h"
#include "Camera.h"
#include <tuple>
#include <map>
#include <vector>

class Construction {
    std::vector<Animation> animations;
    std::map<std::tuple<int, int>, SdlTexture>& explosionRepository;
    int sizeW;
    int sizeH;
    float posX;
    float posY;
    int constType;
    int playerId;
    bool propiety;
    int animationId;
    int lifeId;
    bool isDead;
    SdlTexture* texture;
    SdlTexture* currentLifeTexture;

 public:
    Construction(std::map<std::tuple<int, int>,
                 SdlTexture> &newAnimationsRepository,
                 std::map<int, SdlTexture>& lifeTextures,
                 SdlTexture* identifierTexture,
                 int sizeW,
                 int sizeH,
                 float posX,
                 float posY,
                 int constType,
                 int playerId,
                 bool propiety);

    int render(Camera &camera, int posX, int posY);

    Construction(const Construction& other) = delete;
    Construction& operator=(const Construction& other) = delete;

    Construction(Construction&& other);
    Construction& operator=(Construction&& other);

    void getTexture();
    void getLifeTexture();
    float getX();
    float getY();
    int getConstType();
    bool getPropiety();
    int getWidth();
    int getHeight();
    bool getIsDead();
    void kill();

    void updateLife(int currentLife, int totalLife);

    void update(int delta);

    ~Construction();
};

#endif /*__EXPLOSION_H__*/
