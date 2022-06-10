#include "Unit.h"

Unit::Unit(SDL2pp::Texture &texture): an(texture), facingLeft(false), moving(false), x(300), y(300) {}

Unit::~Unit() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Unit::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Unit::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(x, y, 200, 200), flip);
}

void Unit::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Unit::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Unit::stopMoving() {
    moving = false;
}
