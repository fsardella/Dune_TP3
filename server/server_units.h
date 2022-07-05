#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"
#include "server_buildings.h"
#include "server_weapons.h"
#include "common_command.h"
#include "server_config.h"

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
    MOVING,
    HARVESTING,
    GOING_TO_REFINERY,
    CHARGING_REFINERY
};

class Building;
class Weapon;

class Unit {
    AStar moveAlgorithm;
    coor_t actDest;
    uint16_t actualLife;
    uint16_t totalLife;
    Unit* unitObjv = nullptr;
    Building* buildingObjv = nullptr;
    Weapon* weapon;
    uint16_t id;
    std::string owner;
    uint16_t speed;
    uint16_t speedAcum = 0;
    
    int watchers = 0; // Para asegurarse de que, al destruir,
    // no queden dangling pointers... Es lo que se me ocurre... perdon
    // NOTA DEL FUTURO: YA ES MUY TARDE PARA METER STD::SHARED_POINTERS
    
    void processAttackUnit(std::list<Command>& events);
    void processAttackBuilding(std::list<Command>& events);
    void processIdle(std::list<Command>& events);
 protected:
    void processMove();
    unitStates state = IDLE;
 public:
    Unit(coor_t coor, TerrainMap& terr, uint16_t life, Weapon* weapon,
         uint16_t id, uint16_t speed, std::string owner);
    virtual int getSpeedWeightForMount() = 0;
    int getSpeedWeightForSand();
    int getSpeedWeightForDune();
    int getSpeedWeightForCliff();
    coor_t getPosition();
    uint16_t getID();
    std::string getOwner();
    virtual void update(std::list<Command>& events);
    virtual void setDest(coor_t newDest);
    uint8_t getDir();
    uint16_t getActualLife();
    uint16_t getTotalLife();
    virtual uint8_t getType() = 0;
    virtual bool isHarvester();
    virtual void addPointerToBuildings(std::map<uint16_t, Building*>* buildings) {}
    void print();
    void attack(Unit* attacked);
    void attack(Building* attacked);
    void damage(uint16_t dam);
    virtual uint16_t getDamageFor(Weapon* weapon) = 0;
    bool isDead();
    virtual void die();
    void kill(std::list<Command>& events);

    void watch();
    void stopWatching();
    bool canBeCleaned();

    virtual ~Unit();
};

class Infantry : public Unit {
 public:
    Infantry(coor_t coor, TerrainMap& terr, uint16_t life, Weapon* weapon,
             uint16_t id, uint16_t speed, std::string owner);
    int getSpeedWeightForMount();
    uint16_t getDamageFor(Weapon* weapon);
    virtual ~Infantry();
};


class LightInfantry : public Infantry {
 public:
    LightInfantry(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~LightInfantry();
};

class HeavyInfantry : public Infantry {
 public:
    HeavyInfantry(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~HeavyInfantry();
};

class Fremen : public Infantry {
 public:
    Fremen(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~Fremen();    
};

class Sardaukar : public Infantry {
 public:
    Sardaukar(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~Sardaukar();
};

class Vehicle : public Unit {
 public:
    Vehicle(coor_t coor, TerrainMap& terr, uint16_t life, Weapon* weapon, 
            uint16_t id, uint16_t speed, std::string owner);
    int getSpeedWeightForMount();
    uint16_t getDamageFor(Weapon* weapon);
    virtual ~Vehicle();
};

class Trike : public Vehicle {
 public:
    Trike(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~Trike();
};

class Raider : public Vehicle {
 public:
    Raider(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~Raider();
};

class Tank : public Vehicle {
 public:
    Tank(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~Tank();
};

class Harvester : public Vehicle {
    std::map<uint16_t, Building*>* buildings = nullptr;
    coor_t actHarvestDest;
    Building* ref = nullptr;
    uint32_t actMenage = 0;
    uint32_t menageCap;
    uint16_t harvestingTime = 0;
    uint16_t chargingTime = 0;
    uint16_t harvestTimeLimit;
    uint16_t chargingTimeLimit;
    uint16_t range;
    TerrainMap& terr;

    void processHarvest();
    void processComeback();
    void processCharging();

    void scoutForMenage();
    bool isNextToRefinery();
    bool checkRefineryIntegrity();
 public:
    Harvester(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
              Config* c);
    uint8_t getType();
    bool isHarvester();
    void setDest(coor_t newDest);
    void update(std::list<Command>& events);
    void addPointerToBuildings(std::map<uint16_t, Building*>* buildings);
    void die();
    virtual ~Harvester();
    
};

class Deviator : public Vehicle {
 public:
    Deviator(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c);
    uint8_t getType();
    virtual ~Deviator();
};

class Devastator : public Vehicle {
    uint16_t explosionDamage;
    TerrainMap& terr;
    std::list<Command>& explosionBroadcaster;
 public:
    Devastator(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c, std::list<Command>& events);
    uint8_t getType();
    void die();
    virtual ~Devastator();
};

class SonicTank : public Vehicle {
 public:
    SonicTank(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c, std::list<Command>& events);
    uint8_t getType();
    virtual ~SonicTank();
};

#endif

