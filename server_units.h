#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"
#include "server_buildings.h"


enum unitStates {
    IDLE,  
    ATTACKING_UNIT,
    ATTACKING_BUILDING,
    MOVING
};

class Building;

class Unit {
    AStar moveAlgorithm;
    coor_t actDest;
    unitStates state = IDLE;
    Unit* unitObjv = nullptr;
    Building* buildingObjv = nullptr;
    uint16_t watchers = 0; // Para asegurarse de que, al destruir,
    // no queden dangling pointers... Es lo que se me ocurre... perdon
    
    void processMove();
 public:
 
    Unit(coor_t coor, TerrainMap& terr);
    virtual int getSpeedWeightForMount() = 0;
    int getSpeedWeightForSand();
    int getSpeedWeightForDune();
    int getSpeedWeightForCliff();
    coor_t getPosition();
    void update();
    void setDest(coor_t newDest);
    uint8_t getDir();
    void print();
    void attack(Unit* attacked);
    void attack(Building* attacked);
    void watch();
    void stopWatching();
    bool canBeCleaned();
    virtual ~Unit();
};

class Infantry : public Unit {
 public:
    Infantry(coor_t coor, TerrainMap& terr);
    int getSpeedWeightForMount();
    virtual ~Infantry();
};

class Vehicle : public Unit {
 public:
    Vehicle(coor_t coor, TerrainMap& terr);
    int getSpeedWeightForMount();
    virtual ~Vehicle();
};

#endif

