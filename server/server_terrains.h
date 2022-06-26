#ifndef _SERVER_TERRAINS_H
#define _SERVER_TERRAINS_H

<<<<<<< HEAD
#include <stdint.h>
=======


#include <stdint.h>
#include <set>
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
#include "server_units.h"

class Terrain {
 protected:
<<<<<<< HEAD
    bool occupied;
 public:
    Terrain();
    void occupySpace();
    void freeSpace();
    virtual void print();
    virtual int getSpeed(Unit& unit);
=======
    std::set<coor_t> occupied;
 public:
    Terrain();
    void occupySpace(coor_t coord);
    void freeSpace(coor_t coord);
    bool isOccupied(coor_t coord);
    virtual void print();
    void printDebug();
    virtual int getSpeed(Unit& unit, coor_t coord) = 0;
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    virtual ~Terrain();
};

class Sand : public Terrain {
 public:
    Sand();
<<<<<<< HEAD
    int getSpeed(Unit& unit);
    void print(); // DEBUG
=======
    int getSpeed(Unit& unit, coor_t coord);
    //void print(); // DEBUG
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    virtual ~Sand();
};

class Rock : public Terrain {
    char Building; // TODO CLASE BUILDING
 public:
    Rock();
    void build(char building);
<<<<<<< HEAD
    int getSpeed(Unit& unit);
=======
    int getSpeed(Unit& unit, coor_t coord);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    virtual ~Rock();
};

class Spice : public Terrain {
    uint16_t quantity;
 public:
    Spice(uint16_t quantity);
<<<<<<< HEAD
    int getSpeed(Unit& unit);
=======
    int getSpeed(Unit& unit, coor_t coord);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    virtual ~Spice();
};

class Dune : public Terrain {
 public:
    Dune();
<<<<<<< HEAD
    int getSpeed(Unit& unit);
=======
    int getSpeed(Unit& unit, coor_t coord);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    void print();  // DEBUG
    virtual ~Dune();
};

class Mount : public Terrain {
 public:
    Mount();
<<<<<<< HEAD
    int getSpeed(Unit& unit);
=======
    int getSpeed(Unit& unit, coor_t coord);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    void print();  // DEBUG
    virtual ~Mount();
};

class Cliff : public Terrain {
 public:
    Cliff();
<<<<<<< HEAD
    int getSpeed(Unit& unit);
=======
    int getSpeed(Unit& unit, coor_t coord);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    void print();  // DEBUG
    virtual ~Cliff();
};

#endif


