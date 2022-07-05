#ifndef __SERVER_GUSANO_H__
#define __SERVER_GUSANO_H__

#include <stdint.h>
#include <stdlib.h>
#include <list>
#include "server_terrain_map.h"
#include "server_units.h"
#include "common_command.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

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

class Worm {
    TerrainMap& terr;
    uint32_t delay;
    uint32_t actTime = 0;
    
    void surface(std::list<Command>& events);
    void eatPeople(std::list<Command>& events, coor_t coor);
 public:
    Worm(TerrainMap& terr, uint32_t delay);
    void update(std::list<Command>& events);
    ~Worm();
};

#endif
