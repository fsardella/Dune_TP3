#ifndef __MENUIMAGE_H__
#define __MENUIMAGE_H__

#include "Renderizable.h"

class MenuImage : public Renderizable {
    int rescaling;

    public:
    MenuImage(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY);

    void render(Camera &camera) override;
    void render(Camera &camera, int posX, int posY) override;

    MenuImage(const MenuImage& other) = delete;
    MenuImage& operator=(const MenuImage& other) = delete;

    MenuImage(MenuImage&& other) ;
    MenuImage& operator=(MenuImage&& other) ;

    int getX();
    int getY();

    ~MenuImage();
};

#endif /*__MENUIMAGE_H__*/