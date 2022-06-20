#ifndef __MENUTEXT_H__
#define __MENUTEXT_H__

#include "Renderizable.h"

class MenuText : public Renderizable {
    int rescaling;

    public:
    MenuText(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY);

    void render(Camera &camera) override;
    int render(Camera &camera, int posX, int posY) override;

    MenuText(const MenuText& other) = delete;
    MenuText& operator=(const MenuText& other) = delete;

    MenuText(MenuText&& other) ;
    MenuText& operator=(MenuText&& other) ;

    int getX();
    int getY();

    ~MenuText();
};

#endif /*__MENUTEXT_H__*/