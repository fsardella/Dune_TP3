#ifndef BACKGROUNDTILE_H
#define BACKGROUNDTILE_H

#include "Renderizable.h"

class BackGroundTile : public Renderizable{
    int rescaling;
    
    public:
    BackGroundTile(SdlTexture& texture,
         int sizeW,
         int sizeH,
         int posX,
         int posY);

    // BackGroundTile(SdlTexture& texture,
    //            int sizeW,
    //            int sizeH,
    //            float posX,
    //            float posY,
    //            int rescaling);

    void render(Camera &camera, size_t iteration) override;
    void render(Camera &camera, int posX, int posY) override;

    BackGroundTile(const BackGroundTile& other) = delete;
    BackGroundTile& operator=(const BackGroundTile& other) = delete;

    BackGroundTile(BackGroundTile&& other) ;
    BackGroundTile& operator=(BackGroundTile&& other) ;

    int getX();

    int getY();

    ~BackGroundTile() override;

};


#endif