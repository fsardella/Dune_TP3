#ifndef __AREA_H__
#define __AREA_H__

#include <SDL2/SDL.h>

class Area{
    int x;
    int y;
    int width;
    int height;

 public:
    Area(int x, int y, int width, int height);

    SDL_Rect buildRectangle() const;

    ~Area();
};

#endif /*__AREA_H__*/
