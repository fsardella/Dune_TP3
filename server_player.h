#ifndef __SERVER_PLAYER_H
#define __SERVER_PLAYER_H

#include <stdint.h>
#include <map>
#include <string>
#include "server_units.h"
#include "server_terrain_map.h"

class Player {
    std::string playerName;
    int house;
    std::list<Unit*> units;
    //  TODO BUILDINGS
 public:
    Player(const int& house, const std::string& playerName);
    Player();
    void addUnit(int x, int y, TerrainMap& terr);
    int getHouse();
    std::list<coor_t> getUnits(); // TODO devolver lista de UnitData
    
    ~Player();
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&);
    Player& operator=(Player&&);
};

#endif
