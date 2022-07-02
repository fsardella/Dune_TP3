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
    Building* buildingBirthing = nullptr;
    uint16_t cantLightFactories = 0;
    uint16_t cantHeavyFactories = 0;
    int32_t energy = 0;
    uint32_t moneyCapacity = 0;
    uint32_t money = 4000; // 4000 de dinero inicial... sino no se puede jugar jajsajdj
    std::map<uint16_t, Building*> buildings;
    bool alreadyLost = false;


    uint32_t getPriceOfCreation(uint8_t type);
    bool isBlockInRange(coor_t blockCoord);
    bool isBuildingInRange(Building* toBuild, uint16_t x, uint16_t y);
    bool hasUnit(uint16_t unitID);
    bool hasBuilding(uint16_t buildingID);
    uint16_t getConstructionDelta();
    uint16_t getEnergyPenalization();
 public:
    Player(const int& house, const std::string& playerName, coor_t baseCoords);
    Player();
    
    uint8_t getUnitFactor(uint8_t type);
    coor_t getUnitDir(uint8_t type, TerrainMap& terr);
    
    Unit* getUnit(uint16_t unitID);
    Building* getBuilding(uint16_t buildingID);
    
    bool chargeMoney(uint8_t type);
    void addUnit(Unit* unit);
    uint16_t addBuilding(uint16_t x, uint16_t y, TerrainMap& terr, uint16_t id);
    void createBuilding(uint8_t type);
                     
    void moveUnit(uint16_t unitID, coor_t coor);
    void updateUnits(std::list<Command>& events);            
    void updateBuildings();
    void cleanCorpses(std::map<uint16_t, std::string>& unitIDs,
                      std::map<uint16_t, std::string>& buildingIDs,
                      std::list<Command>& events);
    bool canBeCleaned();

    void buildBase(TerrainMap& terr, uint16_t id);
    coor_t getBaseCoords();
    int getHouse();
    void setID(uint8_t newID);
    uint8_t getID();
    uint32_t getMoney();
    int32_t getEnergy();
    std::list<UnitData> getUnits();
    std::pair<uint8_t, uint8_t> getBuildingInfo();
    
    bool hasLost();
    void kill(std::list<Command>& events);
    
    ~Player();
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&);
    Player& operator=(Player&&);
};

#endif
