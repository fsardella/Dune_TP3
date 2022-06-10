#ifndef AREA_H
#define AREA_H

#include <SDL2/SDL.h>

class Area{
public:
    int x;
    int y;
    int width;
    int height;

	Area(int x, int y, int width, int height);

	SDL_Rect buildRectangle() const;

	~Area();
};


#endif