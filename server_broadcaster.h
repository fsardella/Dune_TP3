#ifndef __SERVER_BROADCASTER_H__
#define __SERVER_BROADCASTER_H__

#include "common_thread.h"
#include "server_activegame.h"
#include "common_command.h"
#include "common_blockingqueue.h"
#include "server_unitbuffer.h"
#include <list>
#include <tuple>
#include <map>

typedef std::map<std::string, BlockingQueue<Command>> queueMap_t;
typedef std::tuple<
        std::map<uint8_t, std::list<UnitData>>, // Units
        std::map<uint8_t, std::pair<uint32_t, int32_t>>, // player, money, energy
        std::list<Command>, // events 
        std::list<UnitBuffer>, // units building
        std::list<Command>, // buildings building
        std::list<std::pair<coor_t, uint8_t>> // Menage
        > broadcast_t;


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
    UNIT_WIP,
    BUILDING_WIP,
    WORM,
    MENAGE
};
#endif

class Broadcaster: public Thread {
    ActiveGame& game;
    queueMap_t& queues;
    BlockingQueue<Command>& queueToKill; // Horripilante, pero viene joya para
    // cerrar todos los hilos de forma elegante

    int broadcast(Command comm);
    Command getUnits(std::map<uint8_t, std::list<UnitData>>& units,
                     std::map<uint8_t, std::pair<uint32_t, int32_t>>& pData);
    Command getUnitsBuilding(std::list<UnitBuffer>& unitsBuilding);
    Command getMenageBroadcast(std::list<std::pair<coor_t, uint8_t>> menageData);
 public:
    Broadcaster(ActiveGame& game, queueMap_t& queues, BlockingQueue<Command>& queueToKill);
    void run() override;
	~Broadcaster() override;
};

#endif
