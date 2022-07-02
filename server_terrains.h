#ifndef _SERVER_TERRAINS_H
#define _SERVER_TERRAINS_H



#include <stdint.h>
#include <map>
#include "server_units.h"
#include "server_buildings.h"

class Terrain {
 protected:
    std::map<coor_t, Unit*> occupiedUnits;
 public:
    Terrain();
    void occupySpace(coor_t coord, Unit* unit);
    Unit* getOccupant(coor_t coord);
    void getAllOccupants(std::list<Unit*>& ret);
    void freeSpace(coor_t coord);
    virtual void eraseBuilding() {}
    bool isOccupied(coor_t coord);
    virtual void print();
    virtual bool canBuild();
    virtual bool isBlocked();
    virtual Building* getBuilding();
    uint16_t virtual harvestMenage(uint16_t freeSpace);
    void printDebug();
    virtual int getSpeedWeight(Unit& unit, coor_t coord) = 0;
    virtual void build(Building* newBuilding) {}
    virtual ~Terrain();
};

class Sand : public Terrain {
 public:
    Sand();
    int getSpeedWeight(Unit& unit, coor_t coord);
    //void print(); // DEBUG
    virtual ~Sand();
};

class Rock : public Terrain {
    Building* building = nullptr;
 public:
    Rock();
    void build(Building* newBuilding);
    bool canBuild();
    bool isBlocked();
    void eraseBuilding();
    Building* getBuilding();
    int getSpeedWeight(Unit& unit, coor_t coord);
    virtual ~Rock();
};

class Spice : public Terrain {
    uint16_t quantity;
 public:
    Spice(uint16_t quantity);
    uint16_t harvestMenage(uint16_t freeSpace);
    int getSpeedWeight(Unit& unit, coor_t coord);
    virtual ~Spice();
};

class Dune : public Terrain {
 public:
    Dune();
    int getSpeedWeight(Unit& unit, coor_t coord);
    void print();  // DEBUG
    virtual ~Dune();
};

class Mount : public Terrain {
 public:
    Mount();
    int getSpeedWeight(Unit& unit, coor_t coord);
    void print();  // DEBUG
    virtual ~Mount();
};

class Cliff : public Terrain {
 public:
    Cliff();
    int getSpeedWeight(Unit& unit, coor_t coord);
    bool isBlocked();
    void print();  // DEBUG
    virtual ~Cliff();
};

#endif


