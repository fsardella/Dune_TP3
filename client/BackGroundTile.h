#ifndef __BACKGROUNDTILE_H__
#define __BACKGROUNDTILE_H__

#include "Renderizable.h"

class BackGroundTile : public Renderizable {
    int rescaling;

 public:
    BackGroundTile(SdlTexture* texture,
         int sizeW,
         int sizeH,
         int posX,
         int posY);

    void render(Camera &camera) override;

    void changeTile(SdlTexture* texture, int x, int y);

    BackGroundTile(const BackGroundTile& other) = delete;
    BackGroundTile& operator=(const BackGroundTile& other) = delete;

    BackGroundTile(BackGroundTile&& other);
    BackGroundTile& operator=(BackGroundTile&& other);

    int getX();

    int getY();

    ~BackGroundTile() override;
};


#endif /*__BACKGROUNDTILE_H__*/
