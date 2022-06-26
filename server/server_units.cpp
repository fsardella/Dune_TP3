#include "server_units.h"


enum TerrType {
    WALL = 0,
    SAND,
    DUNE,
};

Unit::Unit(coor_t coor, TerrainMap& terr):
                                moveAlgorithm(AStar(*this, coor, terr)) {}

Infantry::Infantry(coor_t coor, TerrainMap& terr):
                                Unit(coor, terr) {}

Vehicle::Vehicle(coor_t coor, TerrainMap& terr):
                                Unit(coor, terr) {}


coor_t Unit::getPosition() {
    return this->moveAlgorithm.getPosition();
}

void Unit::processMove(coor_t dest) {
    this->moveAlgorithm.processMove(dest);
}

int Unit::getSpeedForCliff() {
    return WALL;    
}

<<<<<<< HEAD
=======
int Unit::getSpeedForSand() {
    return SAND;
}
int Unit::getSpeedForDune() {
    return DUNE;
}

void Unit::print() {
    this->moveAlgorithm.print();
}

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
Unit::~Unit() {}




<<<<<<< HEAD
int Infantry::getSpeedForSand() {
    return SAND;
}
int Infantry::getSpeedForDune() {
    return DUNE;
}
=======

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
int Infantry::getSpeedForMount() {
    return SAND;
}

Infantry::~Infantry() {}



<<<<<<< HEAD

int Vehicle::getSpeedForSand() {
    return SAND;
}
int Vehicle::getSpeedForDune() {
    return DUNE;
}
=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
int Vehicle::getSpeedForMount() {
    return WALL;
}
Vehicle::~Vehicle() {}
