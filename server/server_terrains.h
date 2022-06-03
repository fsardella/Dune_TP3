#ifndef _SERVER_TERRAINS_H
#define _SERVER_TERRAINS_H

#include <stdint.h>
#include "server_units.h"

class Terrain {
 protected:
    bool occupied;
 public:
    Terrain();
    void occupySpace();
    void freeSpace();
    virtual void print();
    virtual int getSpeed(Unit& unit);
    virtual ~Terrain();
};

class Sand : public Terrain {
 public:
    Sand();
    int getSpeed(Unit& unit);
    void print(); // DEBUG
    virtual ~Sand();
};

class Rock : public Terrain {
    char Building; // TODO CLASE BUILDING
 public:
    Rock();
    void build(char building);
    int getSpeed(Unit& unit);
    virtual ~Rock();
};

class Spice : public Terrain {
    uint16_t quantity;
 public:
    Spice(uint16_t quantity);
    int getSpeed(Unit& unit);
    virtual ~Spice();
};

class Dune : public Terrain {
 public:
    Dune();
    int getSpeed(Unit& unit);
    void print();  // DEBUG
    virtual ~Dune();
};

class Mount : public Terrain {
 public:
    Mount();
    int getSpeed(Unit& unit);
    void print();  // DEBUG
    virtual ~Mount();
};

class Cliff : public Terrain {
 public:
    Cliff();
    int getSpeed(Unit& unit);
    void print();  // DEBUG
    virtual ~Cliff();
};

#endif


