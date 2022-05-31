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

Unit::~Unit() {}




int Infantry::getSpeedForSand() {
    return SAND;
}
int Infantry::getSpeedForDune() {
    return DUNE;
}
int Infantry::getSpeedForMount() {
    return SAND;
}

Infantry::~Infantry() {}




int Vehicle::getSpeedForSand() {
    return SAND;
}
int Vehicle::getSpeedForDune() {
    return DUNE;
}
int Vehicle::getSpeedForMount() {
    return WALL;
}
Vehicle::~Vehicle() {}
