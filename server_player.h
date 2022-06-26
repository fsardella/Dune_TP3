#ifndef __SERVER_PLAYER_H
#define __SERVER_PLAYER_H

#include <stdint.h>
#include <map>
#include <string>
#include "server_units.h"
#include "server_terrain_map.h"
#include "server_unitdata.h"
#include "server_buildings.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

class Player {
    std::string playerName;
    int house;
    std::map<uint16_t, Unit*> units;
    Base base;
    // std::map<uint16_t, Building*> buildings;
    //  TODO BUILDINGS
 public:
    Player(const int& house, const std::string& playerName, coor_t baseCoords);
    Player();
    void addUnit(int x, int y, TerrainMap& terr);
    void buildBase(TerrainMap& terr, uint16_t id);
    coor_t getBaseCoords();
    int getHouse();
    std::list<UnitData> getUnits();
    
    ~Player();
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&);
    Player& operator=(Player&&);
};

#endif
