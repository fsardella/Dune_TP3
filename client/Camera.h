#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Renderizable.h"
#include <map>

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

    SdlTexture blockedTexture;
    SdlTexture menuShadowTexture;
    SdlTexture readyTexture;
    SdlTexture frameTexture;
    SdlTexture constFrameTexture;

    std::map<int, SdlTexture> housesTextures;

    bool isVisibleInX(float x);
    bool isVisibleInY(float y);
    bool isUnitVisible(float x, float y, float txtWidth, float txtHeight);

 public:
    explicit Camera(SdlWindow& window);

    void loadHouseTextures();

    void setMapSize(int width, int height);
    void moveUpwards();
    void moveDownwards();
    void moveLeft();
    void moveRight();

    int getXOffset();
    int getYOffset();

    void render(Renderizable &renderizable);
    void renderInSight(SdlTexture* texture, const Area& src,
                       float posX, float posY);
    int renderInSightForUnit(SdlTexture* texture, const Area& src,
                             float posX, float posY);
    void renderUnitFrame(const Area&src, float posX, float posY);
    void renderInSightForMenu(SdlTexture* texture, const Area& src,
                              float posX, float posY);
    void renderBlockingFigure(int posX, int posY);
    void renderReadyFigure(int posX, int posY);
    void renderMenuFrame(int posX, int posY);
    void renderInSightForMenuTitles(SdlTexture* texture, const Area& src,
                                    float posX, float posY);
    void renderMenuRect();
    void renderShadowForMenu(Area& src, float posX, float posY, int progress);
    void renderColor(SdlTexture* colorTexture);
    void renderHouse(int houseNumber);
    bool isVisible(float x, float y);
    ~Camera();
};

#endif /*__CAMERA_H__*/
