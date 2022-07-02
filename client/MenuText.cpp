#include "MenuText.h"
#include "Camera.h"
#include <utility>

/*
Pre-Condiciones: Constructor del MenuText.
Post-Condiciones: -
*/

MenuText::MenuText(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: Renderizable(texture, sizeW, sizeH, posX, posY) {
    rescaling = 1;
}

/*
Pre-Condiciones: Renderiza el texto del menu.
Post-Condiciones: -
*/

void MenuText::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForMenuTitles(texture, src, posX, posY);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición x del texto del menu.
*/

int MenuText::getX() {
    return posX;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición y del texto del menu.
*/

int MenuText::getY() {
    return posY;
}

/*
Pre-Condiciones: Constructor del MenuText.
Post-Condiciones: -
*/

MenuText::MenuText(MenuText &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}

MenuText& MenuText::operator=(MenuText &&other) {
    if (this == &other) return *this;

    this->rescaling = other.rescaling;

    return *this;
}

/*
Pre-Condiciones: Destructor del MenuText.
Post-Condiciones: -
*/

MenuText::~MenuText() {
}
