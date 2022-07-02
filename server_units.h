#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"
#include "server_buildings.h"
#include "server_weapons.h"
#include "common_command.h"

#ifndef UNITTYPES
#define UNITTYPES
enum unitTypes {
    TRIKE = 0,
    RAIDER,
    TANK,
    HARVESTER,
    DEVIATOR,
    DEVASTATOR,
    SONIC_TANK,
    LIGHT_INFANTRY,
    HEAVY_INFANTRY,
    SARDAUKAR,
    FREMEN
};
#endif


#include <string>

enum unitStates {
    IDLE,  
    ATTACKING_UNIT,
    ATTACKING_BUILDING,
    MOVING
};

class Building;
class Weapon;

class Unit {
    AStar moveAlgorithm;
    coor_t actDest;
    uint16_t actualLife;
    uint16_t totalLife;
    unitStates state = IDLE;
    Unit* unitObjv = nullptr;
    Building* buildingObjv = nullptr;
    Weapon* weapon;
    uint16_t id;
    std::string owner;
    
    uint16_t watchers = 0; // Para asegurarse de que, al destruir,
    // no queden dangling pointers... Es lo que se me ocurre... perdon
    
    void processMove(bool attackingBuilding = false);
    void processAttackUnit();
    void processAttackBuilding();
    void processIdle();
 public:
 
    Unit(coor_t coor, TerrainMap& terr, uint16_t life, Weapon* weapon,
         uint16_t id, std::string owner);
    virtual int getSpeedWeightForMount() = 0;
    int getSpeedWeightForSand();
    int getSpeedWeightForDune();
    int getSpeedWeightForCliff();
    coor_t getPosition();
    uint16_t getID();
    std::string getOwner();
    virtual void update();
    void setDest(coor_t newDest);
    uint8_t getDir();
    virtual uint8_t getType() = 0;
    virtual bool isHarvester();
    virtual void addPointerToBuildings(std::map<uint16_t, Building*>* buildings) {}
    void print();
    void attack(Unit* attacked);
    void attack(Building* attacked);
    void damage(uint16_t dam);
    bool isDead();
    void die();
    void kill(std::list<Command>& events);

    void watch();
    void stopWatching();
    bool canBeCleaned();

    virtual ~Unit();
};

class Infantry : public Unit {
 public:
    Infantry(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner);
    int getSpeedWeightForMount();
    virtual uint8_t getType();
    virtual ~Infantry();
};

class Vehicle : public Unit {
 public:
    Vehicle(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner);
    int getSpeedWeightForMount();
    virtual uint8_t getType();
    virtual ~Vehicle();
};

class Harvester : public Vehicle {
    std::map<uint16_t, Building*>* buildings = nullptr;
    uint32_t actMenage = 0;
    uint32_t menageCap = 200;
    TerrainMap& terr;
 public:
    Harvester(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner);
    uint8_t getType();
    bool isHarvester();
    void update();
    void addPointerToBuildings(std::map<uint16_t, Building*>* buildings);
    virtual ~Harvester();
    
};

#endif

