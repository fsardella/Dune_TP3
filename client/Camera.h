#ifndef CAMERA_H
#define CAMERA_H

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Renderizable.h"

// 32 pixeles (tamaño de tile) <-> 1 metro logico (server)
#define M_TO_P 32

class Camera{
private:
    SdlWindow& window;
    // center width and height
    // depends on screen resolution
    SDL_Point centerPix;

    float logicalCenterX;
    float logicalCenterY;

    int width;
    int height;

    bool isVisibleInX(float x);
    bool isVisibleInY(float y);
    
    public:
    explicit Camera(SdlWindow& window);

    void render(Renderizable &renderizable, size_t iteration);
    void render(Renderizable &renderizable, int x, int y);
    // logical coordinates
    // only renders if visible to player
    void renderInSight(SdlTexture& texture, Area& src,
                       float posX,
                       float posY);
    void renderInSightForUnit(SdlTexture& texture, Area& src,
                       float posX,
                       float posY);
    bool isVisible(float x, float y);
    ~Camera();
};

#endif
