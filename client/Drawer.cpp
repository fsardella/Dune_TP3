#include <unistd.h>
#include "Drawer.h"

Drawer::Drawer(GameView* gameView): gameView(gameView), running(true) {
    printf("se contstruyo\n");
}

void Drawer::run() {
    printf("aca estoy \n");
    size_t it = 0;
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
                gameView->shutdown();
                break;
            }
            // if(event.type == SDL_MOUSEBUTTONDOWN) {
            //     gameView.buildUnit(event.button.x, event.button.y);
            // }
            printf("render\n");
            gameView->render(it);

        }
    }
}

Drawer::~Drawer() {
    this->join();
}