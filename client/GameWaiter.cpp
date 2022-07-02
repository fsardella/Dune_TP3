#include "GameWaiter.h"

GameWaiter::GameWaiter(WaitingWindow& window): window(window) {
    this->start();
}

void GameWaiter::run() {
    window.wait();
}

GameWaiter::~GameWaiter() {
}
