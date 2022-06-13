#include "Camera.h"
#include <iostream>
#include "Renderizable.h"

Camera::Camera(SdlWindow& window)
: window(window),
  logicalCenterX(0),
  logicalCenterY(0) {
    centerPix = window.getCenter();
    width = 2*centerPix.x;
    height = 2*centerPix.y;
}

void Camera::render(Renderizable &renderizable, size_t iteration) {
    renderizable.render(*this, iteration);
}

void Camera::render(Renderizable &renderizable, int x, int y) {
    renderizable.render(*this, x, y);
}

void Camera::renderInSight(SdlTexture& texture, Area& src, float posX, float posY) {
    if (!isVisible(posX, posY)) {
        return;
    }
    auto rect = src.buildRectangle();
    int newX = posX * M_TO_P;
    int newY = posY * M_TO_P;
    Area dst(newX, newY, rect.w, rect.h);
    texture.render(src,dst);
}

void Camera::renderInSightForUnit(SdlTexture& texture, Area& src, float posX, float posY) {
    if (!isVisible(posX, posY)) {
        return;
    }
    auto rect = src.buildRectangle();
    int newX = posX;
    int newY = posY;
    Area dst(newX, newY, rect.w, rect.h);
    texture.render(src,dst);
}

bool Camera::isVisibleInX(float x) {
    auto pixelX = abs(logicalCenterX - x) / M_TO_P;
    return (pixelX >= 0 && pixelX <= width);
}

bool Camera::isVisibleInY(float y) {
    auto pixelY = abs(logicalCenterY - y) / M_TO_P;
    return (pixelY >= 0 && pixelY <= height);
}

bool Camera::isVisible(float x, float y) {
    return isVisibleInX(x) && isVisibleInY(y);
}

Camera::~Camera() {
}
