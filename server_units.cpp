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

int Unit::getSpeedForSand() {
    return SAND;
}
int Unit::getSpeedForDune() {
    return DUNE;
}

Unit::~Unit() {}





int Infantry::getSpeedForMount() {
    return SAND;
}

Infantry::~Infantry() {}



int Vehicle::getSpeedForMount() {
    return WALL;
}
Vehicle::~Vehicle() {}
