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
    virtual bool hasMenage();
    virtual uint16_t peekMenage();
    virtual uint16_t harvestMenage(uint16_t freeSpace);
    virtual bool isSand();
    virtual bool isThereARefinery();
    void printDebug();
    virtual int getSpeedWeight(Unit& unit, coor_t coord) = 0;
    virtual float getSpeedMod();
    virtual void build(Building* newBuilding) {}
    virtual ~Terrain();
};

class Sand : public Terrain {
 public:
    Sand();
    int getSpeedWeight(Unit& unit, coor_t coord) override;
    //void print(); // DEBUG
    bool isSand() override;
    virtual ~Sand();
};

class Rock : public Terrain {
    Building* building = nullptr;
 public:
    Rock();
    void build(Building* newBuilding) override;
    bool canBuild() override;
    bool isBlocked() override;
    bool isThereARefinery() override;
    void eraseBuilding() override;
    Building* getBuilding() override;
    int getSpeedWeight(Unit& unit, coor_t coord) override;
    virtual ~Rock();
};

class Spice : public Terrain {
    uint16_t quantity;
 public:
    explicit Spice(uint16_t quantity);
    uint16_t peekMenage() override;
    uint16_t harvestMenage(uint16_t freeSpace) override;
    bool hasMenage() override;
    int getSpeedWeight(Unit& unit, coor_t coord) override;
    virtual ~Spice();
};

class Dune : public Terrain {
 public:
    Dune();
    int getSpeedWeight(Unit& unit, coor_t coord) override;
    float getSpeedMod() override;
    void print() override;  // DEBUG
    virtual ~Dune();
};

class Mount : public Terrain {
 public:
    Mount();
    int getSpeedWeight(Unit& unit, coor_t coord) override;
    void print() override;  // DEBUG
    virtual ~Mount();
};

class Cliff : public Terrain {
 public:
    Cliff();
    int getSpeedWeight(Unit& unit, coor_t coord) override;
    bool isBlocked() override;
    void print() override;  // DEBUG
    virtual ~Cliff();
};

#endif
