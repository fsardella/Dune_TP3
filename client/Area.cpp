#include "Area.h"


Area::Area(int x, int y, int width, int height)
: x(x), y(y), width(width), height(height) {
}

SDL_Rect Area::buildRectangle() const{
	return SDL_Rect{x, y, width, height};
}

Area::~Area() {
}