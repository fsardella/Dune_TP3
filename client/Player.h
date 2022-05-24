#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"
class Player {
public:
    Player(SDL2pp::Texture &texture);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();
    void getMouseState(int* x, int* y);
private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif // __WORM_H__