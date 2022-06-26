#ifndef _SERVER_UNITS_H
#define _SERVER_UNITS_H


#include "server_astar.h"
#include "server_terrain_map.h"

<<<<<<< HEAD

=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
class Unit {
    AStar moveAlgorithm;
 public:
    Unit(coor_t coor, TerrainMap& terr);
<<<<<<< HEAD
    virtual int getSpeedForSand();
    virtual int getSpeedForDune();
    virtual int getSpeedForMount();
    int getSpeedForCliff();
    coor_t getPosition();
    void processMove(coor_t dest);
=======
    virtual int getSpeedForMount() = 0;
    int getSpeedForSand();
    int getSpeedForDune();
    int getSpeedForCliff();
    coor_t getPosition();
    void processMove(coor_t dest);
    void print();
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    virtual ~Unit();
};

class Infantry : public Unit {
 public:
    Infantry(coor_t coor, TerrainMap& terr);
<<<<<<< HEAD
    int getSpeedForSand();
    int getSpeedForDune();
=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    int getSpeedForMount();
    virtual ~Infantry();
};

class Vehicle : public Unit {
 public:
    Vehicle(coor_t coor, TerrainMap& terr);
<<<<<<< HEAD
    int getSpeedForSand();
    int getSpeedForDune();
=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    int getSpeedForMount();
    virtual ~Vehicle();
};

#endif

