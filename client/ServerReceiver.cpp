
#include "ServerReceiver.h"

ServerReceiver::ServerReceiver(GameView &gameView): drawer(gameView) {
    drawer.start();
}

void ServerReceiver::run() {}

ServerReceiver::~ServerReceiver() {
	drawer.join();
}