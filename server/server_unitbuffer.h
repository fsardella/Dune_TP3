#ifndef __SERVER_UNITBUFFER_H__
#define __SERVER_UNITBUFFER_H__

#include <stdint.h>
#include <string>
#include <list>
#include <tuple>
#include "common_command.h"
#include "server_units.h"
#include "server_config.h"



class UnitBuffer {
    Config* c;
    uint16_t totalCount;
    uint16_t count;
    uint8_t type;
    std::string playerName;
    uint8_t playerID;
    coor_t coor;
    TerrainMap& terr;
    std::list<Command>& events; // Para la explosion del Destructor
    std::list<std::pair<uint16_t, std::string>>& swappedUnits; // Para el Deviator

 public:
    UnitBuffer(uint8_t type, std::string playerName,
               TerrainMap& terr, uint8_t playerID, Config* c,
               std::list<Command>& events,
               std::list<std::pair<uint16_t, std::string>>& swappedUnits);
    bool willItEnd(uint16_t seconds);
    void process(uint16_t seconds);
    uint8_t getType();
    uint8_t getTimeToEnd();
    std::string getPlayerName();
    uint8_t getPlayerID();
    Unit* getResult(coor_t coor, uint16_t newID);
    ~UnitBuffer();
};

#endif
