#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"

class Unit {
    AStar moveAlgorithm;
 public:
    Unit(coor_t coor, TerrainMap& terr);
    virtual int getSpeedForMount() = 0;
    int getSpeedForSand();
    int getSpeedForDune();
    int getSpeedForCliff();
    coor_t getPosition();
    void processMove(coor_t dest);
    void print();
    virtual ~Unit();
};

class Infantry : public Unit {
 public:
    Infantry(coor_t coor, TerrainMap& terr);
    int getSpeedForMount();
    virtual ~Infantry();
};

class Vehicle : public Unit {
 public:
    Vehicle(coor_t coor, TerrainMap& terr);
    int getSpeedForMount();
    virtual ~Vehicle();
};

#endif

