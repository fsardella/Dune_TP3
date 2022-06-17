#include <iostream>
#include "MenuScreen.h"
#include "Camera.h"

MenuScreen::MenuScreen() {
}

void MenuScreen::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSight(src, posX, posY);
}

int MenuScreen::getX() {
    return posX;
}

int MenuScreen::getY() {
    return posY;
}

MenuScreen::MenuScreen(MenuScreen &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}


MenuScreen::~MenuScreen() {
}