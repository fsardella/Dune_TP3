#include "MenuText.h"
#include "Camera.h"
#include <utility>

MenuText::MenuText(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: Renderizable(texture, sizeW, sizeH, posX, posY) {
    rescaling = 1;
}

void MenuText::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForMenuTitles(texture, src, posX, posY);
}

int MenuText::getX() {
    return posX;
}

int MenuText::getY() {
    return posY;
}

MenuText::MenuText(MenuText &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}

MenuText& MenuText::operator=(MenuText &&other) {
    if (this == &other) return *this;

    this->rescaling = other.rescaling;

    return *this;
}


MenuText::~MenuText() {
}
