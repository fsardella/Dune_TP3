#ifndef _SERVER_TERRAINS_H
#define _SERVER_TERRAINS_H



#include <stdint.h>
#include <set>
#include "server_units.h"

class Terrain {
 protected:
    std::set<coor_t> occupied;
 public:
    Terrain();
    void occupySpace(coor_t coord);
    void freeSpace(coor_t coord);
    bool isOccupied(coor_t coord);
    virtual void print();
    virtual int getSpeed(Unit& unit, coor_t coord) = 0;
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
    char Building; // TODO CLASE BUILDING
 public:
    Rock();
    void build(char building);
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
    void print();  // DEBUG
    virtual ~Cliff();
};

#endif


