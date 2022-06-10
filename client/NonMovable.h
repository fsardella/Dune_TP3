#ifndef TILE_H
#define TILE_H

#include "Renderizable.h"

class NonMovable : public Renderizable{
    int rescaling;
    
    public:
    NonMovable(SdlTexture& texture,
         int sizeW,
         int sizeH,
         float posX,
         float posY);

    NonMovable(SdlTexture& texture,
               int sizeW,
               int sizeH,
               float posX,
               float posY,
               int rescaling);

    void render(Camera &camera, size_t iteration) override;
    void render(Camera &camera, int posX, int posY) override;

    NonMovable(const NonMovable& other) = delete;
    NonMovable& operator=(const NonMovable& other) = delete;

    NonMovable(NonMovable&& other) ;
    NonMovable& operator=(NonMovable&& other) ;

    float getX();

    float getY();

    ~NonMovable() override;

};


#endif