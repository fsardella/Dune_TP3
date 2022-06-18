#include "Camera.h"
#include "Renderizable.h"

#include <iostream>

#define MENU_OFFSET_X 995
#define MENU_OFFSET_Y 100
#define SPACING_X 0
#define SPACING_Y 10

Camera::Camera(SdlWindow& window)
: window(window),
  offsetX(0),
  offsetY(0) {
    centerPix = window.getCenter();
    width = int((centerPix.x) * 1.5 / TILE_PIX_SIZE);
    height = int(2*centerPix.y / TILE_PIX_SIZE);
}

void Camera::render(Renderizable &renderizable) {
    renderizable.render(*this);
}

void Camera::render(Renderizable &renderizable, int x, int y) {
    renderizable.render(*this, x, y);
}

void Camera::setMapSize(int width, int height) {
    this->mapWidth = width;
    this->mapHeight = height;
}

void Camera::renderInSight(SdlTexture& texture, Area& src, float posX, float posY) {
    if (!isVisible(posX, posY)) {
        return;
    }
    auto rect = src.buildRectangle();
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    Area dst(newX, newY, rect.w, rect.h);
    texture.render(src,dst);
}

void Camera::renderInSightForUnit(SdlTexture& texture, Area& src, float posX, float posY) {
    auto rect = src.buildRectangle();
    if (!isUnitVisible(posX, posY, rect.w, rect.h)) {
        return;
    }
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    Area dst(newX, newY, rect.w, rect.h);
    texture.render(src,dst);
}

void Camera::renderInSightForMenu(SdlTexture& texture, Area& src, float posX, float posY) {
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    texture.render(src,dst);
}

bool Camera::isVisibleInX(float x) {
    return (x >= offsetX && x <= width + offsetX);
}

bool Camera::isVisibleInY(float y) {
    return (y >= offsetY && y <= height + offsetY);
}

bool Camera::isVisible(float x, float y) {
    return isVisibleInX(x) && isVisibleInY(y);
}

bool Camera::isUnitVisible(float x, float y, float txtWidth, float txtHeight) {
    if (isVisible(x, y)) return true;
    return (x + (txtWidth / TILE_PIX_SIZE) > offsetX && y + (txtHeight /TILE_PIX_SIZE) > offsetY);
}

void Camera::moveUpwards() {
    if (offsetY - 1 < 0) {
        return;
    }
    offsetY -= 1;
}

void Camera::moveDownwards() {
    if (offsetY + 1 > mapWidth - offsetY) {
        return;
    }
    offsetY += 1;
}

void Camera::moveLeft() {
    if (offsetX - 1 < 0) {
        return;
    }
    offsetX -= 1;
}

void Camera::moveRight() {
    if (offsetX + 1 > mapWidth - offsetX) {
        return;
    }
    offsetX += 1;
}

Camera::~Camera() {
}
