#ifndef __WORM_H__
#define __WORM_H__

#include <vector>
#include "Animation.h"
#include "Camera.h"

class Worm {
    Animation attackAnimation;
    int sizeW;
    int sizeH;
    float posX;
    float posY;
    bool isCurrentlyAttacking;
    SdlTexture* texture;

 public:
    Worm(std::vector<SdlTexture*> emptyTextures,
         int sizeW,
         int sizeH,
         float posX,
         float posY);

    int render(Camera &camera, float posX, float posY);

    Worm(const Worm& other) = delete;
    Worm& operator=(const Worm& other) = delete;

    Worm(Worm&& other);
    Worm& operator=(Worm&& other);

    void getTexture();

    float getX();
    float getY();
    int getWidth();
    int getHeight();

    void setNewPosition(float x, float y);

    void setTextures(std::vector<SdlTexture*> textures);

    bool isAttacking();
    void startAttacking();

    void update(int delta);

    ~Worm();
};


#endif /*__WORM_H__*/
