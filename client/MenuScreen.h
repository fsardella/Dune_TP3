#ifndef MENUSCREEN_H
#define MENUSCREEN_H

class MenuScreen {
    // int rescaling;
    int sizeW = 100; 
    int sizeH = 700
    int posX = 110
    int posY = 110
    
    public:
    MenuScreen();

    void render(Camera &camera);
    // void render(Camera &camera, int posX, int posY) override;

    MenuScreen(const MenuScreen& other) = delete;
    MenuScreen& operator=(const MenuScreen& other) = delete;

    MenuScreen(MenuScreen&& other) ;
    MenuScreen& operator=(MenuScreen&& other) ;

    int getX();

    int getY();

    ~MenuScreen() override;

};


#endif