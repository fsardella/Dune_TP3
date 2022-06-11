#include <unistd.h>
#include "Drawer.h"

Drawer::Drawer(GameView &gameView): gameView(gameView), running(true) {
}

void Drawer::run() {
    size_t it = 0;
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
                gameView.shutdown();
                break;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                gameView.buildUnit(event.button.x, event.button.y);
            }
            gameView.render(it);

        }
    }
}

Drawer::~Drawer() {
}