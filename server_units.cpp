#include "server_units.h"


enum TerrType {
    WALL = 0,
    SAND,
    DUNE,
};

#define CHUNKSIZE 8

Unit::Unit(coor_t coor, TerrainMap& terr, uint16_t life,
           Weapon* weapon, uint16_t id, std::string owner):
                                moveAlgorithm(AStar(*this, coor, terr)),
                                actualLife(life),
                                totalLife(life),
                                weapon(weapon),
                                id(id),
                                owner(owner) {}

Infantry::Infantry(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner):
                                Unit(coor, terr, 50,
                                     new AssaultRifle(terr, 3), id, owner) {}

Vehicle::Vehicle(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner):
                                Unit(coor, terr, 80,
                                     new AssaultRifle(terr, 4), id, owner) {}


coor_t Unit::getPosition() {
    return this->moveAlgorithm.getPosition();
}

uint8_t Unit::getDir() {
    return this->moveAlgorithm.getDir();
}

uint16_t Unit::getID() {
    return this->id;
}

std::string Unit::getOwner() {
    return this->owner;
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

void Unit::damage(uint16_t dam) {
    if (this->actualLife < dam) {
        if (!this->isDead())
            this->die();
        this->actualLife = 0;
    } else {
        this->actualLife -= dam;
    }
}

bool Unit::isDead() {
    return (this->actualLife == 0);
}

void Unit::die() {
    this->moveAlgorithm.eraseUnitFromMap();
}

void Unit::kill() {
    if (!this->isDead())
        this->die();
    this->actualLife = 0;
}

void Unit::processMove(bool attackingBuilding) {
    this->weapon->stopAttack();
    bool ret = this->moveAlgorithm.processMove(this->actDest, attackingBuilding);
    if (ret) {
        if (this->actDest == this->moveAlgorithm.getPosition())
            this->state = IDLE;
    } else {
        this->actDest = this->moveAlgorithm.getPosition();
        this->state = IDLE;
    }
}

void Unit::processAttackUnit() {
    if (this->unitObjv == nullptr) {
        this->state = IDLE;
        this->weapon->stopAttack();
        return;
    }
    if (this->unitObjv->isDead()) {
        this->unitObjv->stopWatching();
        this->unitObjv = nullptr;
        this->weapon->stopAttack();
        this->state = IDLE;
        return;
    }
    this->actDest = this->unitObjv->getPosition();
    if (this->weapon->isInRange(this, this->unitObjv)) {
        this->weapon->startAttack();
        if (this->weapon->attack(this->unitObjv))
            ;// Se agrega a los eventos
    } else {
        this->processMove();
    }
}

void Unit::processAttackBuilding() {
    if (this->buildingObjv == nullptr) {
        this->state = IDLE;
        this->weapon->stopAttack();
        return;
    }
    if (this->buildingObjv->destroyed()) {
        this->buildingObjv->stopWatching();
        this->buildingObjv = nullptr;
        this->weapon->stopAttack();
        this->state = IDLE;
        return;
    }
    if (this->weapon->isInRange(this, this->buildingObjv)) {
        this->weapon->startAttack();
        if (this->weapon->attack(this->buildingObjv))
            ;// Se agrega a los eventos
    } else {
        this->processMove(true);
    }
}

void Unit::processIdle() {
    Unit* tempObjv = this->weapon->scout(this);
    if (tempObjv == nullptr) {
        this->weapon->stopAttack();
        return;
    }
    this->weapon->startAttack();
    if (this->weapon->attack(tempObjv))
        ;// Se agrega a los eventos

}


void Unit::update() {
    this->weapon->update();
    switch (this->state) {
        case IDLE:
            this->processIdle();
            break;
        case ATTACKING_UNIT:
            this->processAttackUnit();
            break;
        case ATTACKING_BUILDING:
            this->processAttackBuilding();
            break;
        case MOVING:
            this->processMove();
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
    if (!this->isDead())
        return false;
    return (this->watchers == 0);
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

Unit::~Unit() {
    delete this->weapon;  
}





int Infantry::getSpeedWeightForMount() {
    return SAND;
}

uint8_t Infantry::getType() {
    return 7;
}

Infantry::~Infantry() {}



int Vehicle::getSpeedWeightForMount() {
    return WALL;
}

uint8_t Vehicle::getType() {
    return 0;
}
Vehicle::~Vehicle() {}
