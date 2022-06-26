#include "Camera.h"

#include <iostream>

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 700
#define MENU_OFFSET_X 991
#define MENU_OFFSET_Y 100
#define SPACING_X 2
#define SPACING_Y 10
#define SUCCESS 0

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

int Camera::render(Renderizable &renderizable, int x, int y) {
    return renderizable.render(*this, x, y);
}

void Camera::setMapSize(int width, int height) {
    this->mapWidth = width;
    this->mapHeight = height;
}

void Camera::renderInSight(SdlTexture* texture, Area& src, float posX, float posY) {
    if (!isVisible(posX, posY)) {
        return;
    }
    auto rect = src.buildRectangle();
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    Area dst(newX, newY, rect.w, rect.h);
    texture->render(src, dst);
}

int Camera::renderInSightForUnit(SdlTexture* texture, Area& src, float posX, float posY) {
    auto rect = src.buildRectangle();
    if (!isUnitVisible(posX, posY, rect.w, rect.h)) {
        return SUCCESS;
    }
    int returnValue = SUCCESS;
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    int remainderX = (posX + (rect.w / TILE_PIX_SIZE)) - (width + offsetX + 1);
    int remainderY = (posY + (rect.h / TILE_PIX_SIZE)) - (height + offsetY + 1);
    int txtWidth = rect.w;
    int txtHeight = rect.h;
    if (remainderX > 0) {
        returnValue = 1;
    }
    if (remainderY > 0) {
        returnValue = 1;
    }
    Area dst(newX, newY, txtWidth, txtHeight);
    texture->render(src, dst);
    return returnValue;
}

void Camera::renderMenuRect() {
    SDL_Rect r;
    r.x = MENU_OFFSET_X;
    r.y = 0;
    r.w = WINDOW_WIDTH - MENU_OFFSET_X;
    r.h = WINDOW_HEIGHT;

    window.renderRect(r);
}

void Camera::renderInSightForMenu(SdlTexture* texture, Area& src, float posX, float posY) {
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    texture->render(src,dst);
}

void Camera::renderInSightForMenuTitles(SdlTexture* texture, Area& src, float posX, float posY) {
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    texture->render(src,dst);
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
    bool condLeft = (x + (txtWidth / TILE_PIX_SIZE) > offsetX);
    bool condRight = (x / TILE_PIX_SIZE < offsetX);
    bool condUp = (txtHeight / TILE_PIX_SIZE) > offsetY;
    bool condDown = (y / TILE_PIX_SIZE < offsetY);
    return ((condLeft || condRight) && (condUp || condDown));
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

<<<<<<< HEAD
=======
int Camera::getXOffset() {
    return offsetX;
}
    
int Camera::getYOffset() {
    return offsetY;
}

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
Camera::~Camera() {
}
