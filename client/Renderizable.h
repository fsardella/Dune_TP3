#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H
#include "SdlTexture.h"

class Camera;

class Renderizable {
    protected:
    SdlTexture& texture;
    int sizeW;
    int sizeH;
    float posX;
    float posY;
    public:
    explicit Renderizable(SdlTexture& texture,
                          int sizeW,
                          int sizeH,
                          float posX,
                          float posY);

    Renderizable(const Renderizable& other) = delete;
    Renderizable& operator=(const Renderizable& other) = delete;

    Renderizable(Renderizable&& other);

    virtual void render(Camera &camera, size_t iteration) = 0;
    virtual void render(Camera &camera, int posX, int posY) = 0;

    virtual ~Renderizable();
};


#endif