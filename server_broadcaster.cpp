#include "server_broadcaster.h"
#include <time.h> 
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "server_unitbuffer.h"

Broadcaster::Broadcaster(ActiveGame& game, queueMap_t& queues,
                         BlockingQueue<Command>& queueToKill)
: game(game),
queues(queues),
queueToKill(queueToKill) {}


Command Broadcaster::getUnits() {
    Command comm;
    comm.add8BytesMessage(UNIT_BROADCAST);
    comm.setType(UNIT_BROADCAST);
    std::map<uint8_t, std::list<UnitData>> units = this->game.getUnits();
    int totalQuantity = units.size();
    comm.add16BytesMessage((uint16_t)totalQuantity);
    for (auto& playerUnits : units) {
        comm.add8BytesMessage(playerUnits.first);
        comm.add16BytesMessage(playerUnits.second.size());
        for (UnitData& unit : playerUnits.second) {
            comm.add16BytesMessage(unit.pos.second);
            comm.add16BytesMessage(unit.pos.first);
            comm.add8BytesMessage(unit.type);
            comm.add8BytesMessage(unit.dir);
            comm.add16BytesMessage(unit.id);
        } 
    }
    return comm;
}


Command Broadcaster::getUnitsBuilding() {
    Command comm;
    comm.add8BytesMessage(UNIT_WIP);
    comm.setType(UNIT_WIP);
    std::list<UnitBuffer> unitsBuilding = this->game.receiveUnitBuffer();
    comm.add16BytesMessage(unitsBuilding.size());
    for (UnitBuffer& u : unitsBuilding) {
        comm.add8BytesMessage(u.getPlayerID());
        comm.add8BytesMessage(u.getType());
        comm.add8BytesMessage(u.getTimeToEnd());
    }
    return comm;   
}

int Broadcaster::broadcast(Command comm) {
    int countPlayers = 0;
    if (comm.getType() == WON_GAME || comm.getType() == LOST_GAME) {
        try {
            queues[comm.getSender()].push(comm);
            // Ya se que no es sender sino receiver,
            // pero estoy harto de bloatear de metodos y atributos
        } catch (const ClosedQueueException&) {}
        return 0x1; // El 1 es medio sus, pero bue, funca cualquier numero que no sea 0.
        // En hexa para que parezca mas cheto. 
    }
    for (auto& q : queues) {
        try {
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


void Broadcaster::run() {
    int countPlayers;
    clock_t before, after;
    do {
        before = clock();
        Command comm = this->getUnits();
        countPlayers = this->broadcast(comm);
        comm = this->getUnitsBuilding();
        countPlayers = this->broadcast(comm);
        std::list<Command> comms = this->game.receiveEvents();
        for (Command c : comms) // Si hace falta, cambio broadcast para que reciba
                                // una lista y aprovecho localidad del cache
            this->broadcast(c);
        after = clock();
        if ((after - before) > DELTA) {
            std::cout << "WARNING: desincronizacion de reloj. Considere reducir su frecuencia."
                      << std::endl;
            continue;
        }
        usleep(DELTA - (after - before));
    } while (countPlayers > 0);
    this->game.endGame();
    this->queueToKill.close();
}


Broadcaster::~Broadcaster() {
    this->join();    
}