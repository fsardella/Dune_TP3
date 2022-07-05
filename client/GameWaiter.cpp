#include "GameWaiter.h"

/*
Pre-Condiciones: Constructor del GameWaiter.
Post-Condiciones: -
*/

GameWaiter::GameWaiter(WaitingWindow& window): window(window) {
    this->start();
}

/*
Pre: Se espera a que se llegue a la cantidad de jugadores requeridos para
poder cerrar la ventana de espera e iniciar el juego.
Post: -
*/

void GameWaiter::run() {
    window.wait();
}

/*
Pre-Condiciones: Destructor del GameWaiter.
Post-Condiciones: -
*/

GameWaiter::~GameWaiter() {
}
