#include "Worm.h"
#include <utility>

#define OFFSET_X 16
#define OFFSET_Y 16

/*
Pre-Condiciones: Constructor de gusano de arena.
Post-Condiciones: -
*/

Worm::Worm(std::vector<SdlTexture*> emptyTextures,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: attackAnimation(std::move(emptyTextures)),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  isCurrentlyAttacking(false),
  texture(nullptr) {
}

/*
Pre-Condiciones: Renderiza el gusano de arena.
Post-Condiciones: - 
*/

int Worm::render(Camera &camera, float posX, float posY) {
    Area src(0, 0, sizeW, sizeH);
    float offsetX = static_cast<float>(OFFSET_X) /
                    static_cast<float>(TILE_PIX_SIZE);
    float offsetY = static_cast<float>(OFFSET_Y) /
                    static_cast<float>(TILE_PIX_SIZE);
    float positionX = posX + offsetX;
    float positionY = posY + offsetY;
    return camera.renderInSightForUnit(texture, src, positionX, positionY);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición x del gusano de arena. 
*/

float Worm::getX() {
    return posX;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición y del gusano de arena. 
*/

float Worm::getY() {
    return posY;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el ancho del gusano de arena. 
*/

int Worm::getWidth() {
    return sizeW;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el largo del gusano de arena. 
*/

int Worm::getHeight() {
    return sizeH;
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina la nueva posición del gusano de arena. 
*/

void Worm::setNewPosition(float x, float y) {
    posX = x;
    posY = y;
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina la textura del gusano de arena del gusano de arena. 
*/

void Worm::setTextures(std::vector<SdlTexture*> textures) {
    attackAnimation.setTextures(std::move(textures));
    attackAnimation.setFrameDuration(5000);
    getTexture();
}

/*
Pre-Condiciones: -
Post-Condiciones: Setea la textura del gusano de arena del gusano de arena. 
*/

void Worm::getTexture() {
    texture = attackAnimation.getTexture();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el gusano de arena esta atacando o false si no.
*/

bool Worm::isAttacking() {
    return isCurrentlyAttacking;
}

/*
Pre-Condiciones: Comienza el ataque del gusano de arena.
Post-Condiciones: -
*/

void Worm::startAttacking() {
    isCurrentlyAttacking = true;
    attackAnimation.reset();
}

/*
Pre-Condiciones: Actualiza la textura del gusano de arena.
Post-Condiciones: -
*/

void Worm::update(int delta) {
    if (attackAnimation.isLastFrame()) {
        isCurrentlyAttacking = false;
        return;
    }
    attackAnimation.update(delta);
    getTexture();
}

/*
Pre-Condiciones: Constructor de gusano de arena.
Post-Condiciones: -
*/

Worm::Worm(Worm &&other)
: attackAnimation(std::move(other.attackAnimation)),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  isCurrentlyAttacking(other.isCurrentlyAttacking),
  texture(other.texture)
{}

/*
Pre-Condiciones: Destructor de gusano de arena.
Post-Condiciones: -
*/

Worm::~Worm() {
}
