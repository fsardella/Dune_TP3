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
    bool isUnitVisible(float x, float y, float txtWidth, float txtHeight);
    
    public:
    explicit Camera(SdlWindow& window);

    void setMapSize(int width, int height);
    void moveUpwards();
    void moveDownwards();
    void moveLeft();
    void moveRight();

    int getXOffset();
    int getYOffset();

    void render(Renderizable &renderizable);
    int render(Renderizable &renderizable, int x, int y);
    void renderInSight(SdlTexture* texture, Area& src,
                       float posX,
                       float posY);
    int renderInSightForUnit(SdlTexture* texture, Area& src,
                       float posX,
                       float posY);
    void renderInSightForMenu(SdlTexture* texture, Area& src,
                       float posX,
                       float posY);
    void renderInSightForMenuTitles(SdlTexture* texture, Area& src, float posX, float posY);
    void renderMenuRect();

    bool isVisible(float x, float y);

    ~Camera();
};

#endif
