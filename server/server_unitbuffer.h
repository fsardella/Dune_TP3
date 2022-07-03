#ifndef __SERVER_UNITBUFFER_H__
#define __SERVER_UNITBUFFER_H__

#include <stdint.h>
#include <string>

#include "server_units.h"



class UnitBuffer {
    uint16_t totalCount;
    uint16_t count;
    uint8_t type;
    std::string playerName;
    uint8_t playerID;
    coor_t coor;
    TerrainMap& terr;

 public:
    UnitBuffer(uint8_t type, std::string playerName,
               TerrainMap& terr, uint8_t playerID);
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
