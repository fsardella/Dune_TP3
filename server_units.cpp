#include "server_units.h"


enum TerrType {
    WALL = 0,
    SAND,
    DUNE,
};

#define CHUNKSIZE 8

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
    return this->moveAlgorithm.getDir();
}

void Unit::setDest(coor_t newDest) {
    if (this->buildingObjv != nullptr)
        this->buildingObjv->stopWatching();
    this->buildingObjv = nullptr;
    if (this->unitObjv != nullptr)
        this->unitObjv->stopWatching();
    this->unitObjv = nullptr;
    this->state = MOVING;
    this->actDest = newDest;
}


void Unit::attack(Unit* attacked) {
    if (this->buildingObjv != nullptr)
        this->buildingObjv->stopWatching();
    this->buildingObjv = nullptr;
    this->unitObjv = attacked;
    this->unitObjv->watch();
    this->state = ATTACKING_UNIT;
    this->actDest = attacked->getPosition();
}

void Unit::attack(Building* attacked) {
    if (this->unitObjv != nullptr)
        this->unitObjv->stopWatching();
    this->unitObjv = nullptr;
    this->buildingObjv = attacked;
    this->buildingObjv->watch();
    this->state = ATTACKING_BUILDING;
    coor_t attackedPos = attacked->getPosition();
    coor_t attackedDims = attacked->getSize();
    this->actDest = coor_t(attackedPos.first + attackedDims.first * CHUNKSIZE / 2,
                           attackedPos.second + attackedDims.second * CHUNKSIZE / 2);
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
        case ATTACKING_UNIT:
            break;
        case ATTACKING_BUILDING:
            break;
        case MOVING:
            processMove();
            break;
    }
}


void Unit::watch() {
    this->watchers++;
}


void Unit::stopWatching() {
    if (this->canBeCleaned())
        return;
    this->watchers--;
}

bool Unit::canBeCleaned() {
    return watchers == 0;
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
