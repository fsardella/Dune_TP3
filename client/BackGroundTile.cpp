#include "BackGroundTile.h"
#include "Camera.h"
#include <utility>

/*
Pre: Constuctor de la clase BackGroundTile.
Post: -
*/

BackGroundTile::BackGroundTile(SdlTexture* texture,
           int sizeW,
           int sizeH,
           int posX,
           int posY,
           int id)
: Renderizable(texture, sizeW, sizeH, posX, posY), id(id) {
    rescaling = 1;
}

/*
Pre: Se renderiza una tile del background.
Post: -
*/

void BackGroundTile::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSight(texture, src, posX, posY);
}

/*
Pre: Se cambia la textura para una tile del background.
Post: -
*/

void BackGroundTile::changeTile(SdlTexture* texture, int x, int y, int index) {
    this->texture = texture;
    this->posX = x;
    this->posY = y;
    this->id = id;
}

/*
Pre: Se obtiene la posición x de una tile del background.
Post: -
*/

int BackGroundTile::getX() {
    return posX;
}

/*
Pre: Se obtiene la posición y de una tile del background.
Post: -
*/

int BackGroundTile::getY() {
    return posY;
}

int BackGroundTile::getId() {
    return id;
}

/*
Pre: Constuctor de la clase BackGroundTile.
Post: -
*/

BackGroundTile::BackGroundTile(BackGroundTile &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling) {
}

/*
Pre: Destructor de la clase BackGroundTile.
Post: -
*/

BackGroundTile::~BackGroundTile() {
}
