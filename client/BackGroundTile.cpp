#include "BackGroundTile.h"
#include "Camera.h"

BackGroundTile::BackGroundTile(SdlTexture &texture,
           int sizeW,
           int sizeH,
           int posX,
           int posY)
: Renderizable(texture, sizeW, sizeH, posX, posY) {
    rescaling = 1;
}

void BackGroundTile::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSight(texture, src, posX, posY);
}

void BackGroundTile::render(Camera &camera, int posX, int posY) {
}

int BackGroundTile::getX() {
    return posX;
}

int BackGroundTile::getY() {
    return posY;
}

BackGroundTile::BackGroundTile(BackGroundTile &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}

BackGroundTile::~BackGroundTile() {
}
