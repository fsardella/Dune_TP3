#ifndef CAMERA_H
#define CAMERA_H

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Renderizable.h"

#define TILE_PIX_SIZE 32

class Camera{
private:
    SdlWindow& window;
    SDL_Point centerPix;

    float offsetX;
    float offsetY;

    int mapWidth;
    int mapHeight;

    int width;
    int height;

    bool isVisibleInX(float x);
    bool isVisibleInY(float y);
    
    public:
    explicit Camera(SdlWindow& window);

    void setMapSize(int width, int height);
    void moveUpwards();
    void moveDownwards();
    void moveLeft();
    void moveRight();

    void render(Renderizable &renderizable);
    void render(Renderizable &renderizable, int x, int y);
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
