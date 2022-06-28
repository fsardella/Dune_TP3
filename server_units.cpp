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

uint8_t Unit::getDir() {
    return 0;
}

void Unit::setDest(coor_t newDest) {
    this->state = MOVING;
    this->actDest = newDest;
}

void Unit::processMove() {
    bool ret = this->moveAlgorithm.processMove(this->actDest);
    if (ret) {
        if (this->actDest == this->moveAlgorithm.getPosition())
            this->state = IDLE;
        else
            this->state = MOVING;
    } else {
        this->actDest = this->moveAlgorithm.getPosition();
        this->state = IDLE;
    }
}

void Unit::update() {
    switch (this->state) {
        case IDLE:
            break;
        case ATTACKING:
            break;
        case MOVING:
            processMove();
            break;
    }
}

int Unit::getSpeedWeightForCliff() {
    return WALL;    
}

int Unit::getSpeedWeightForSand() {
    return SAND;
}
int Unit::getSpeedWeightForDune() {
    return DUNE;
}

void Unit::print() {
    this->moveAlgorithm.print();
}

Unit::~Unit() {}





int Infantry::getSpeedWeightForMount() {
    return SAND;
}

Infantry::~Infantry() {}



int Vehicle::getSpeedWeightForMount() {
    return WALL;
}
Vehicle::~Vehicle() {}
