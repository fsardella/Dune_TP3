#ifndef __RENDERIZABLE_H__
#define __RENDERIZABLE_H__

#include "SdlTexture.h"

class Camera;

class Renderizable {
 protected:
    SdlTexture* texture;
    int sizeW;
    int sizeH;
    float posX;
    float posY;

 public:
    explicit Renderizable(SdlTexture* texture,
                          int sizeW,
                          int sizeH,
                          float posX,
                          float posY);

    Renderizable(const Renderizable& other) = delete;
    Renderizable& operator=(const Renderizable& other) = delete;

    Renderizable(Renderizable&& other);

    virtual void render(Camera &camera) = 0;

    virtual ~Renderizable();
};


#endif /*__RENDERIZABLE_H__*/
