#include "server_timewizard.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>

TimeWizard::TimeWizard(ActiveGame& game, Config* c): delta(c->CLOCK_DELTA),
                                                           game(game) {}


void TimeWizard::run() {
    clock_t before, after;
    while (this->game.isAlive()) {
        before = clock();
        this->game.update();
        after = clock();
        if ((after - before) > this->delta) {
            std::cout << "WARNING: desincronizacion de reloj. Considere reducir su frecuencia."
                      << std::endl;
            continue;
        }
        usleep(this->delta - (after - before));
    }
}


TimeWizard::~TimeWizard() {
    this->join();
}
