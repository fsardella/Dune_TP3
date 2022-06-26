#include "server_timewizard.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>

TimeWizard::TimeWizard(ActiveGame& game): game(game) {}


#define DELTA 100000
// POSIX: 1s == 1M ticks, 100K ticks -> 1/10 seg

void TimeWizard::run() {
    clock_t before, after;
    while (this->game.isAlive()) {
        before = clock();
        //  GAME -> (mutexed) -> MAKE TIME HAPPEN
        after = clock();
        if ((after - before) > DELTA) {
            std::cout << "WARNING: desincronizacion de reloj. Considere reducir su frecuencia."
                      << std::endl;
            continue;
        }
        usleep(DELTA - (after - before));
    }
}


TimeWizard::~TimeWizard() {
    this->join();
}
