#include <unistd.h>
#include <iostream>
#include "Drawer.h"

#define DRAWER_FRAME_DURATION 100

Drawer::Drawer(GameView* gameView): gameView(gameView) {
}

void Drawer::run() {
    while (gameView->isRunning()) {
        auto start = std::chrono::steady_clock::now();
        gameView->render();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> elapsed = (end - start);
        int delta = elapsed.count();
        gameView->update(DRAWER_FRAME_DURATION);
        if (DRAWER_FRAME_DURATION > delta) {
            usleep(DRAWER_FRAME_DURATION - delta);
        } else {
            std::cout << "Please increase the DRAWER_FRAME_DURATION" << std::endl;
        }
    }
}

Drawer::~Drawer() {
}