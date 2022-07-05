#include "Area.h"

/*
Pre: Constuctor de la clase area.
Post: -
*/

Area::Area(int x, int y, int width, int height)
: x(x), y(y), width(width), height(height) {
}

/*
Pre: Se construye un rectángulo y se devuelve una vez construido.
Post: -
*/

SDL_Rect Area::buildRectangle() const {
    return SDL_Rect{x, y, width, height};
}

/*
Pre: Destructor de la clase area.
Post: -
*/

Area::~Area() {
}
