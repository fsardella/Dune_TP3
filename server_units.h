#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"

class Unit {
    AStar moveAlgorithm;
 public:
    Unit(coor_t coor, TerrainMap& terr);
    virtual int getSpeedForSand() = 0;
    virtual int getSpeedForDune() = 0;
    virtual int getSpeedForMount() = 0;
    int getSpeedForCliff();
    coor_t getPosition();
    void processMove(coor_t dest);
    virtual ~Unit();
};

class Infantry : public Unit {
 public:
    Infantry(coor_t coor, TerrainMap& terr);
    int getSpeedForSand();
    int getSpeedForDune();
    int getSpeedForMount();
    virtual ~Infantry();
};

class Vehicle : public Unit {
 public:
    Vehicle(coor_t coor, TerrainMap& terr);
    int getSpeedForSand();
    int getSpeedForDune();
    int getSpeedForMount();
    virtual ~Vehicle();
};

#endif

