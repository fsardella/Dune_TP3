#ifndef __SERVER_PLAYER_H
#define __SERVER_PLAYER_H

#include <stdint.h>
#include <map>
#include <list>
#include <string>
#include "server_units.h"
#include "server_terrain_map.h"
#include "server_unitdata.h"
#include "server_buildings.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

class Player {
    std::string playerName;
    uint8_t playerID = 0xFF;
    int house;
    std::map<uint16_t, Unit*> units;
    Base base;
    uint16_t cantLightFactories = 0;
    std::map<uint16_t, Building*> buildings;
    
    void addSpecialBuilding(uint8_t type);
    bool isBlockInRange(coor_t blockCoord);
    bool isBuildingInRange(Building* toBuild, uint16_t x, uint16_t y);
    bool hasUnit(uint16_t unitID);
    bool hasBuilding(uint16_t buildingID);
 public:
    Player(const int& house, const std::string& playerName, coor_t baseCoords);
    Player();
    
    uint8_t getUnitFactor(uint8_t type);
    coor_t getUnitDir(uint8_t type, TerrainMap& terr);
    
    Unit* getUnit(uint16_t unitID);
    Building* getBuilding(uint16_t buildingID);
    
    void addUnit(Unit* unit);
    bool addBuilding(uint8_t type, uint16_t x, uint16_t y, TerrainMap& terr,
                     uint16_t id);
    void moveUnit(uint16_t unitID, coor_t coor);
    void updateUnits();            
    
    void buildBase(TerrainMap& terr, uint16_t id);
    coor_t getBaseCoords();
    int getHouse();
    void setID(uint8_t newID);
    uint8_t getID();
    std::list<UnitData> getUnits();
    
    ~Player();
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&);
    Player& operator=(Player&&);
};

#endif
