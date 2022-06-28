#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"


enum unitStates {
    IDLE,  
    MOVING,
    ATTACKING
};

class Unit {
    AStar moveAlgorithm;
    coor_t actDest;
    unitStates state = IDLE;
    
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

