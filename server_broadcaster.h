#ifndef __SERVER_BROADCASTER_H__
#define __SERVER_BROADCASTER_H__

#include "common_thread.h"
#include "server_activegame.h"
#include "common_command.h"
#include "common_blockingqueue.h"
#include "server_unitbuffer.h"

typedef std::map<std::string, BlockingQueue<Command>> queueMap_t;

#ifndef BROADCASTOPERS
#define BROADCASTOPERS
enum broadcastOpers {
    SUCCESS = 0,
    FAILURE,
    UNIT_BROADCAST,
    BUILDING_BUILT,
    UNIT_ATTACKED,
    BUILDING_ATTACKED,
    LOST_GAME,
    WON_GAME,
    UNIT_WIP
};
#endif

class Broadcaster: public Thread {
    ActiveGame& game;
    queueMap_t& queues;
    BlockingQueue<Command>& queueToKill; // Horripilante, pero viene joya para
    // cerrar todos los hilos de forma elegante

    int broadcast(Command comm);
    Command getUnits();
    Command getUnitsBuilding();
 public:
    Broadcaster(ActiveGame& game, queueMap_t& queues, BlockingQueue<Command>& queueToKill);
    void run() override;
	~Broadcaster() override;
};

#endif