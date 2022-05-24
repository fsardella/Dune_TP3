//
// Created by fedemgp on 14/05/22.
//

#ifndef QT5_DEMO_GAMELOOP_H
#define QT5_DEMO_GAMELOOP_H

#include "SDL2pp/SDL2pp.hh"
#include "Player.h"

class Gameloop {
    SDL2pp::Renderer &renderer;
    Player player;
    bool running;

    void handle_events();
    void update(float dt);
    void render();

public:
    Gameloop(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture);
    void run();
};

#endif //QT5_DEMO_GAMELOOP_H
