#ifndef __UNIT_H__
#define __UNIT_H__

#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"

class Unit {
public:
    Unit(SDL2pp::Texture &texture);
    ~Unit();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif // __UNIT_H__