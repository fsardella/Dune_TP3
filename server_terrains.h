#ifndef _SERVER_TERRAINS_H
#define _SERVER_TERRAINS_H



#include <stdint.h>
#include <map>
#include "server_units.h"

class Terrain {
 protected:
    std::map<coor_t, uint16_t> occupiedUnits;
 public:
    Terrain();
    void occupySpace(coor_t coord, uint16_t id);
    uint16_t getIdOfOccupant(coor_t coord);
    void freeSpace(coor_t coord);
    bool isOccupied(coor_t coord);
    virtual void print();
    virtual bool canBuild();
    virtual bool isBlocked();
    void printDebug();
    virtual int getSpeed(Unit& unit, coor_t coord) = 0;
    virtual void build(TerrainMap& terr, uint16_t) {}
    virtual ~Terrain();
};

class Sand : public Terrain {
 public:
    Sand();
    int getSpeed(Unit& unit, coor_t coord);
    //void print(); // DEBUG
    virtual ~Sand();
};

class Rock : public Terrain {
    uint16_t building_id;
    bool built = false;
 public:
    Rock();
    void build(uint16_t building);
    bool canBuild();
    bool isBlocked();
    int getSpeed(Unit& unit, coor_t coord);
    virtual ~Rock();
};

class Spice : public Terrain {
    uint16_t quantity;
 public:
    Spice(uint16_t quantity);
    int getSpeed(Unit& unit, coor_t coord);
    virtual ~Spice();
};

class Dune : public Terrain {
 public:
    Dune();
    int getSpeed(Unit& unit, coor_t coord);
    void print();  // DEBUG
    virtual ~Dune();
};

class Mount : public Terrain {
 public:
    Mount();
    int getSpeed(Unit& unit, coor_t coord);
    void print();  // DEBUG
    virtual ~Mount();
};

class Cliff : public Terrain {
 public:
    Cliff();
    int getSpeed(Unit& unit, coor_t coord);
    bool isBlocked();
    void print();  // DEBUG
    virtual ~Cliff();
};

#endif


