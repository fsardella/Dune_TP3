#include "server_broadcaster.h"
#include <time.h> 
#include <unistd.h>
#include <cstdlib>
#include <iostream>

Broadcaster::Broadcaster(ActiveGame& game, queueMap_t& queues,
                         BlockingQueue<Command>& queueToKill)
: game(game),
queues(queues),
queueToKill(queueToKill) {}


Command Broadcaster::getUnits(std::string recvName) {
    Command comm;
    std::map<std::string, std::list<UnitData>> units = this->game.getUnits();
    int totalQuantity = units.size();
    comm.add16BytesMessage((uint16_t)totalQuantity);


    for (const auto& u: units) {
        if (u.first == recvName) {
            comm.add16BytesMessage((uint16_t)u.second.size());
            comm.add8BytesMessage((uint8_t)u.second.front().getHouse());
            for (UnitData data : u.second) {
                comm.add16BytesMessage((uint16_t)data.getPos().second);
                comm.add16BytesMessage((uint16_t)data.getPos().first);
                comm.add8BytesMessage(0); // Unit Type
            }
        }
    }

    for (const auto& u: units) {
        if (u.first == recvName) {
            continue;
        }
        comm.add16BytesMessage((uint16_t)u.second.size());
        comm.add8BytesMessage((uint8_t)u.second.front().getHouse());
        for (UnitData data : u.second) {
            comm.add16BytesMessage((uint16_t)data.getPos().second);
            comm.add16BytesMessage((uint16_t)data.getPos().first);
            comm.add8BytesMessage(0); // Unit Type
        }
    }

    return comm;
}


int Broadcaster::broadcast(/*Command comm*/) {
    int countPlayers = 0;
    for (auto& q : queues) {
        try {
            Command comm = this->getUnits(q.first);
            q.second.push(comm);
            countPlayers++;
        } catch (const ClosedQueueException&) {
            continue;
        }
    }
    
    return countPlayers;
}

#define DELTA 100000
// POSIX: 1s == 1M ticks, 100K ticks -> 1/10 seg
// usleep recibe una cantidad de microsegundos, no de ticks (la cuenta es la misma igualmente)


void Broadcaster::run() {
    int countPlayers;
    clock_t before, after;
    do {
        before = clock();
        // GetGameData --> Command comm
        countPlayers = this->broadcast(/*comm*/);
        after = clock();
        if ((after - before) > DELTA) {
            std::cout << "WARNING: desincronizacion de reloj. Considere reducir su frecuencia."
                      << std::endl;
            continue;
        }
        usleep(DELTA - (after - before)); // Esta cuenta salió bien acá, pero no en el Drawer del cliente
    } while (countPlayers > 0);
    this->game.endGame();
    this->queueToKill.close();
}


Broadcaster::~Broadcaster() {
    this->join();    
}
