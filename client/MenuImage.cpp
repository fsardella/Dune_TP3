#include "MenuImage.h"
#include "Camera.h"

MenuImage::MenuImage(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: Renderizable(texture, sizeW, sizeH, posX, posY) {
    rescaling = 1;
}

void MenuImage::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForMenu(texture, src, posX, posY);
}

int MenuImage::render(Camera &camera, int posX, int posY) {
    return 0;
}

int MenuImage::getX() {
    return posX;
}

int MenuImage::getY() {
    return posY;
}

MenuImage::MenuImage(MenuImage &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}

MenuImage::~MenuImage() {
}
