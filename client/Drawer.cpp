#include <unistd.h>
#include "Drawer.h"

Drawer::Drawer(GameView* gameView): gameView(gameView) {
}

void Drawer::run() {
    while (gameView->isRunning()) {
        gameView->render();
    }
}

Drawer::~Drawer() {
}