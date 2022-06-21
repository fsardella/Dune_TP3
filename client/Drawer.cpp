#include <unistd.h>
#include "Drawer.h"

Drawer::Drawer(GameView* gameView): gameView(gameView) {
}

void Drawer::run() {
    while (gameView->isRunning()) {
        auto start = std::chrono::steady_clock::now();
        gameView->render();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> elapsed = (end - start);
        int delta = elapsed.count();
        gameView->update(delta);
    }
}

Drawer::~Drawer() {
}