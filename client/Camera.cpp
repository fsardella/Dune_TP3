#include "Camera.h"

#include <iostream>

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 700
#define MENU_OFFSET_X 991
#define MENU_OFFSET_Y 100
#define END_MENU_Y 620
#define SPACING_X 2
#define SPACING_Y 10
#define SUCCESS 0

#define BLOCKED_PATH "../client/menuImgs/blocked.bmp"
#define SHADOW_PATH "../client/menuImgs/sombra.bmp"
#define READY_PATH "../client/menuImgs/ready.bmp"
#define FRAME_PATH "../client/animations/frame.bmp"
#define CONST_FRAME_PATH "../client/menuImgs/marco.bmp"
#define MENU_WIDTH 100
#define MENU_HEIGHT 75
#define COLOR_WIDTH 50
#define COLOR_HEIGHT 50
#define COLOR_OFFSET_X 230

#define WHITE_COLOR 255
#define BLACK_COLOR 0
#define OPACITY 180

/*
Pre: Constuctor de la clase Camera.
Post: -
*/

Camera::Camera(SdlWindow& window)
: window(window),
  offsetX(0),
  offsetY(0),
  mapWidth(0),
  mapHeight(0),
  width(static_cast<int>((window.getCenter().x) * 1.5 / TILE_PIX_SIZE)),
  height(static_cast<int>(2*window.getCenter().y / TILE_PIX_SIZE)),
  blockedTexture(BLOCKED_PATH, &window, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR),
  menuShadowTexture(SHADOW_PATH, &window, SDL_BLENDMODE_BLEND, OPACITY),
  readyTexture(READY_PATH, &window, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR),
  frameTexture(FRAME_PATH, &window, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR),
  constFrameTexture(CONST_FRAME_PATH, &window, BLACK_COLOR, BLACK_COLOR, BLACK_COLOR) {
    this->loadHouseTextures();
}

/*
Pre: Carga las texturas de las distintas casas.
Post: -
*/

void Camera::loadHouseTextures() {
    for (int i = 0; i < 3; i ++) {
        std::string path("../client/menuImgs/house" + std::to_string(i) + ".bmp");
        housesTextures.emplace(std::piecewise_construct,
                               std::forward_as_tuple(i),
                               std::forward_as_tuple(path, &window,
                               WHITE_COLOR, WHITE_COLOR, WHITE_COLOR));
    }
}

/*
Pre: Renderizador para la camara.
Post: -
*/

void Camera::render(Renderizable &renderizable) {
    renderizable.render(*this);
}

void Camera::setMapSize(int width, int height) {
    this->mapWidth = width;
    this->mapHeight = height;
}

/*
Pre: Renderizador para la camara.
Post: -
*/

void Camera::renderInSight(SdlTexture* texture, const Area& src, float posX,
                           float posY) {
    if (!isVisible(posX, posY)) {
        return;
    }
    auto rect = src.buildRectangle();
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    Area dst(newX, newY, rect.w, rect.h);
    texture->render(src, dst);
}

/*
Pre: Renderizador de unidades para la camara.
Post: -
*/

int Camera::renderInSightForUnit(SdlTexture* texture, const Area& src, float posX,
                                 float posY) {
    auto rect = src.buildRectangle();
    if (!isUnitVisible(posX, posY, rect.w, rect.h)) {
        return SUCCESS;
    }
    int returnValue = SUCCESS;
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    int remainderX = (posX + (rect.w / TILE_PIX_SIZE)) - (width + offsetX + 1);
    int remainderY = (posY + (rect.h / TILE_PIX_SIZE)) -
                     (height + offsetY + 1);
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

/*
Pre: Renderizador de frame de unidades para la camara.
Post: -
*/

void Camera::renderUnitFrame(const Area&src, float posX, float posY) {
    auto rect = src.buildRectangle();
    if (!isUnitVisible(posX, posY, rect.w, rect.h)) {
        return;
    }
    int newX = (posX - offsetX) * TILE_PIX_SIZE;
    int newY = (posY - offsetY) * TILE_PIX_SIZE;
    int txtWidth = rect.w;
    int txtHeight = rect.h;
    Area dst(newX, newY, txtWidth, txtHeight);
    frameTexture.render(src, dst);
}

/*
Pre: Renderizador de rectangulo del menu para la camara.
Post: -
*/

void Camera::renderMenuRect() {
    SDL_Rect r;
    r.x = MENU_OFFSET_X;
    r.y = 0;
    r.w = WINDOW_WIDTH - MENU_OFFSET_X;
    r.h = WINDOW_HEIGHT;

    window.renderRect(r);
}

/*
Pre: Renderizador de la sombra para simular la construccion de 
edificios o entrenamiento de unidades.
Post: -
*/

void Camera::renderShadowForMenu(Area& src, float posX, float posY,
                                 int progress) {
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * MENU_HEIGHT +
               MENU_HEIGHT * (static_cast<float>(progress) /
               static_cast<float>(100));

    Area dst(newX, newY, rect.w, rect.h);
    menuShadowTexture.render(src, dst);
}

/*
Pre: Renderizador del menu para la camara.
Post: -
*/

void Camera::renderInSightForMenu(SdlTexture* texture, const Area& src,
                                  float posX, float posY) {
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    texture->render(src, dst);
}

/*
Pre: Renderizador del bloqueo de unidades y/o construcciones
para cuando no estan disponibles para el jugador.
Post: -
*/

void Camera::renderBlockingFigure(int posX, int posY) {
    Area src(0, 0, MENU_WIDTH, MENU_HEIGHT);
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    blockedTexture.render(src, dst);
}

/*
Pre: Renderizador del ready de construcciones
para cuando ya están construidas y disponibles para que el jugador
pueda posicionarlas donde el desee.
Post: -
*/

void Camera::renderReadyFigure(int posX, int posY) {
    Area src(0, 0, MENU_WIDTH, MENU_HEIGHT);
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    readyTexture.render(src, dst);
}

/*
Pre: Renderizador un marco para representar cuando una imagen del
menu fue seleccionada.
Post: -
*/

void Camera::renderMenuFrame(int posX, int posY) {
    Area src(0, 0, MENU_WIDTH, MENU_HEIGHT);
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = MENU_OFFSET_Y + (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    constFrameTexture.render(src, dst);
}

/*
Pre: Renderizador del bloqueo de unidades y/o construcciones
para cuando no estan disponibles para el jugador.
Post: -
*/

void Camera::renderInSightForMenuTitles(SdlTexture* texture, const Area& src,
                                        float posX, float posY) {
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + (posX + 1) * SPACING_X + posX * rect.w;
    int newY = (posY + 1) * SPACING_Y + posY * rect.h;
    Area dst(newX, newY, rect.w, rect.h);
    texture->render(src, dst);
}

/*
Pre: Renderizador del color del jugador para la camara.
Post: -
*/

void Camera::renderColor(SdlTexture* colorTexture) {
    Area src(0, 0, COLOR_WIDTH, COLOR_HEIGHT);
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + COLOR_OFFSET_X;
    int newY = END_MENU_Y + SPACING_Y;
    Area dst(newX, newY, rect.w, rect.h);
    colorTexture->render(src, dst);
}

/*
Pre: Renderizador de la casa del jugador para la camara.
Post: -
*/

void Camera::renderHouse(int houseNumber) {
    Area src(0, 0, MENU_WIDTH, MENU_HEIGHT);
    auto rect = src.buildRectangle();
    int newX = MENU_OFFSET_X + 3 * SPACING_X + MENU_WIDTH;
    int newY = END_MENU_Y;
    Area dst(newX, newY, rect.w, rect.h);
    housesTextures.at(houseNumber).render(src, dst);
}

/*
Pre: Chequea si una posición es visible en x.
Post: -
*/

bool Camera::isVisibleInX(float x) {
    return (x >= offsetX && x <= width + offsetX);
}

/*
Pre: Chequea si una posición es visible en y.
Post: -
*/

bool Camera::isVisibleInY(float y) {
    return (y >= offsetY && y <= height + offsetY);
}

/*
Pre: Chequea si una posición es visible en x y en y.
Post: -
*/

bool Camera::isVisible(float x, float y) {
    return isVisibleInX(x) && isVisibleInY(y);
}

/*
Pre: Chequea si una unidad dado una posicion (x, y) y un 
ancho y largo es visible en la camara.
Post: -
*/

bool Camera::isUnitVisible(float x, float y, float txtWidth, float txtHeight) {
    if (isVisible(x, y)) return true;
    bool condLeft = (x + (txtWidth / TILE_PIX_SIZE) > offsetX);
    bool condRight = (x / TILE_PIX_SIZE < offsetX);
    bool condUp = (txtHeight / TILE_PIX_SIZE) > offsetY;
    bool condDown = (y / TILE_PIX_SIZE < offsetY);
    return ((condLeft || condRight) && (condUp || condDown));
}

/*
Pre: -
Post: La camara se mueve para arriba.
*/

void Camera::moveUpwards() {
    if (offsetY - 1 < 0) {
        return;
    }
    offsetY -= 1;
}

/*
Pre: -
Post: La camara se mueve para abajo.
*/

void Camera::moveDownwards() {
    if (offsetY + 1 > mapHeight - height) {
        return;
    }
    offsetY += 1;
}

/*
Pre: -
Post: La camara se mueve para la izquierda.
*/

void Camera::moveLeft() {
    if (offsetX - 1 < 0) {
        return;
    }
    offsetX -= 1;
}

/*
Pre: -
Post: La camara se mueve para la derecha.
*/

void Camera::moveRight() {
    if (offsetX + 1 > mapWidth - width) {
        return;
    }
    offsetX += 1;
}

/*
Pre: -
Post: Se obtiene el offset de x.
*/

int Camera::getXOffset() {
    return offsetX;
}

/*
Pre: -
Post: Se obtiene el offset de y.
*/

int Camera::getYOffset() {
    return offsetY;
}

/*
Pre: Destructor de la clase Camera.
Post: -
*/

Camera::~Camera() {
}
