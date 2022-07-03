#include "server_units.h"
#include <iostream>

enum TerrType {
    WALL = 0,
    SAND,
    DUNE,
};


#ifndef BROADCASTOPERS
#define BROADCASTOPERS
enum broadcastOpers {
    SUCCESS = 0,
    FAILURE,
    UNIT_BROADCAST,
    BUILDING_BUILT,
    UNIT_ATTACKED,
    BUILDING_ATTACKED,
    LOST_GAME,
    WON_GAME,
    UNIT_WIP,
    BUILDING_WIP,
    WORM,
    MENAGE
};
#endif

#define CHUNKSIZE 8

Unit::Unit(coor_t coor, TerrainMap& terr, uint16_t life,
           Weapon* weapon, uint16_t id, uint16_t speed, std::string owner):
                                moveAlgorithm(AStar(*this, coor, terr)),
                                actualLife(life),
                                totalLife(life),
                                weapon(weapon),
                                id(id),
                                owner(owner),
                                speed(speed) {}

Infantry::Infantry(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner):
                            Unit(coor, terr, 50,
                                 new AssaultRifle(terr, 3), id, 16, owner) {}

Vehicle::Vehicle(coor_t coor, TerrainMap& terr, uint16_t id,
                std::string owner, uint16_t speed):
                            Unit(coor, terr, 80,
                                 new AssaultRifle(terr, 4), id, speed, owner) {}


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


uint16_t Unit::getActualLife() {
    return this->actualLife;
}

uint16_t Unit::getTotalLife() {
    return this->totalLife;
}

bool Unit::isHarvester() {
    return false;
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

void Unit::kill(std::list<Command>& events) {
    if (!this->isDead()) {
        this->die();
        Command dead;
        dead.add8BytesMessage(UNIT_ATTACKED);
        dead.add16BytesMessage(0xFFFF);
        dead.add16BytesMessage(this->id);
        dead.add16BytesMessage(0);
        dead.add16BytesMessage(this->totalLife);
        events.push_back(dead);
    }
    this->actualLife = 0;
}

void Unit::processMove(bool attackingBuilding) {
    this->moveAlgorithm.print();
    this->weapon->stopAttack();
    this->speedAcum += this->speed * this->moveAlgorithm.getSpeedMod();
    uint8_t steps = this->speedAcum / 30;
    this->speedAcum = this->speedAcum % 30;
    for (uint8_t i = 0; i < steps; i++) {
        bool ret = this->moveAlgorithm.processMove(this->actDest, attackingBuilding);
        if (ret) {
            if (this->actDest == this->moveAlgorithm.getPosition()) {
                this->state = IDLE;
                break;
            }
        } else {
            this->actDest = this->moveAlgorithm.getPosition();
            this->state = IDLE;
            break;
        }
    }
}

void Unit::processAttackUnit(std::list<Command>& events) {
    if (this->unitObjv == nullptr) {
        this->state = IDLE;
        this->weapon->stopAttack();
        return;
    }
    if (this->unitObjv->isDead() || this->unitObjv->getOwner() == this->owner) {
        this->unitObjv->stopWatching();
        this->unitObjv = nullptr;
        this->weapon->stopAttack();
        this->state = IDLE;
        return;
    }
    this->actDest = this->unitObjv->getPosition();
    if (this->weapon->isInRange(this, this->unitObjv)) {
        this->weapon->startAttack();
        if (this->weapon->attack(this->unitObjv)) {
            Command attack;
            attack.add8BytesMessage(UNIT_ATTACKED);
            attack.setType(UNIT_ATTACKED);
            attack.add16BytesMessage(this->id);
            attack.add16BytesMessage(this->unitObjv->getID());
            attack.add16BytesMessage(this->unitObjv->getActualLife());
            attack.add16BytesMessage(this->unitObjv->getTotalLife());
            events.push_back(attack);
    }
    } else {
        this->processMove();
    }
}

void Unit::processAttackBuilding(std::list<Command>& events) {
    if (this->buildingObjv == nullptr) {
        this->state = IDLE;
        this->weapon->stopAttack();
        return;
    }
    if (this->buildingObjv->destroyed() ||
        this->buildingObjv->getOwner() == this->owner) {
        this->buildingObjv->stopWatching();
        this->buildingObjv = nullptr;
        this->weapon->stopAttack();
        this->state = IDLE;
        return;
    }
    if (this->weapon->isInRange(this, this->buildingObjv)) {
        this->weapon->startAttack();
        if (this->weapon->attack(this->buildingObjv)) {
            Command attack;
            attack.add8BytesMessage(BUILDING_ATTACKED);
            attack.setType(BUILDING_ATTACKED);
            attack.add16BytesMessage(this->id);
            attack.add16BytesMessage(this->buildingObjv->getID());
            attack.add16BytesMessage(this->buildingObjv->getActualLife());
            attack.add16BytesMessage(this->buildingObjv->getTotalLife());
            events.push_back(attack);
        }
    } else {
        this->processMove(true);
    }
}

void Unit::processIdle(std::list<Command>& events) {
    Unit* tempObjv = this->weapon->scout(this);
    if (tempObjv == nullptr) {
        this->weapon->stopAttack();
        return;
    }
    this->weapon->startAttack();
    if (this->weapon->attack(tempObjv)) {
        Command attack;
        attack.add8BytesMessage(UNIT_ATTACKED);
        attack.setType(UNIT_ATTACKED);
        attack.add16BytesMessage(this->id);
        attack.add16BytesMessage(tempObjv->getID());
        attack.add16BytesMessage(tempObjv->getActualLife());
        attack.add16BytesMessage(tempObjv->getTotalLife());
        events.push_back(attack);
    }
}


void Unit::update(std::list<Command>& events) {
    this->weapon->update();
    switch (this->state) {
        case IDLE:
            this->processIdle(events);
            break;
        case ATTACKING_UNIT:
            this->processAttackUnit(events);
            break;
        case ATTACKING_BUILDING:
            this->processAttackBuilding(events);
            break;
        case MOVING:
            std::cout << "empezo el movimiento\n";
            this->processMove();
            std::cout << "termino el movimiento\n";
            break;
        default:
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


Harvester::Harvester(coor_t coor, TerrainMap& terr, uint16_t id,
                     std::string owner) : Vehicle(coor, terr, id, owner, 12),
                                          terr(terr) {}

uint8_t Harvester::getType() {
    return HARVESTER;
}   

bool Harvester::isHarvester() {
    return true;
}

void Harvester::setDest(coor_t newDest) {
    Vehicle::setDest(newDest);
    if (!this->terr.hasMenage(newDest))
        return;
    this->actHarvestDest = newDest;
    this->state = HARVESTING;
}

bool Harvester::checkRefineryIntegrity() {
    coor_t newDest;
    if (this->ref == nullptr || this->ref->destroyed()) {
        if (this->ref != nullptr) {
            this->ref->stopWatching();
            this->ref = nullptr;
        }
        for (auto& b : *this->buildings) {
            if (b.second->isRefinery()) {
                this->ref = b.second;
                this->ref->watch();
                coor_t pos = b.second->getPosition();
                coor_t dims = b.second->getSize();
                newDest = coor_t(pos.first + dims.first * CHUNKSIZE / 2,
                            pos.second + dims.second * CHUNKSIZE / 2);
                Vehicle::setDest(newDest);
                return true;
            }
        }
        return false;
    }
    coor_t pos = this->ref->getPosition();
    coor_t dims = this->ref->getSize();
    newDest = coor_t(pos.first + dims.first * CHUNKSIZE / 2,
                    pos.second + dims.second * CHUNKSIZE / 2);
    Vehicle::setDest(newDest);
    return true;
}

void Harvester::processHarvest() {
    if (this->getPosition() != this->actHarvestDest) {
        this->processMove();
        return;
    }
    if (!this->terr.hasMenage(this->actHarvestDest)) {
        this->harvestingTime = 0;
        this->scoutForMenage();
        return;
    }
    this->harvestingTime += 1;
    if (this->harvestingTime >= 200) {
        this->harvestingTime = 0;
        this->actMenage += this->terr.harvestMenage(this->getPosition(),
                                            this->menageCap - this->actMenage);
        if (this->actMenage != this->menageCap)
            return;
        if (!this->checkRefineryIntegrity()) {
            this->state = IDLE;
            return;
        }
        this->state = GOING_TO_REFINERY;
    }
}

void Harvester::scoutForMenage() {
    coor_t pos = this->actHarvestDest;
    for (int i = -CHUNKSIZE * 5; i <= CHUNKSIZE * 5; i += CHUNKSIZE) {
        for (int j = -CHUNKSIZE * 5; i <= CHUNKSIZE * 5; i += CHUNKSIZE) {
            if (abs(i) + abs(j) > 5)
                continue;
            if (this->terr.hasMenage(coor_t(pos.first + i,
                                            pos.second + j))) {
                this->actHarvestDest = coor_t(pos.first + i,
                                            pos.second + j);
                Vehicle::setDest(this->actHarvestDest);
                this->state = HARVESTING;
                return;
            }
        } 
    }
    this->state = GOING_TO_REFINERY;
}

bool Harvester::isNextToRefinery() {
    coor_t pos = this->getPosition();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (this->terr.isThereARefinery(coor_t(pos.first + i,
                                                   pos.second + j)))
                return true;
        }
    }
    return false;
}


void Harvester::processComeback() {
    if (!this->checkRefineryIntegrity()) {
        this->state = IDLE;
        return;
    }
    if (this->isNextToRefinery())
        if (this->actMenage == 0)
            this->state = IDLE;
        else
            this->state = CHARGING_REFINERY;
    else 
        this->processMove(true);
}

void Harvester::processCharging() {
    Building* aux = this->ref;
    if (!this->checkRefineryIntegrity()) {
        this->chargingTime = 0;
        this->state = IDLE;
        return;
    }
    this->state = CHARGING_REFINERY;
    if (aux != this->ref) {
        this->chargingTime = 0;
        this->state = GOING_TO_REFINERY;
        return;
    }
    this->chargingTime += 1;
    if (this->chargingTime >= 50) {
        this->chargingTime = 0;
        if (!this->terr.hasMenage(this->actHarvestDest)) {
            this->scoutForMenage();
            return;
        }
        Vehicle::setDest(this->actHarvestDest);
        this->state = HARVESTING;
    }
}

void Harvester::update(std::list<Command>& events) {
    switch (this->state) {
        case MOVING:
            this->processMove();
            break;
        case HARVESTING:
            this->processHarvest();
            this->chargingTime = 0;
            return;
        case GOING_TO_REFINERY:
            this->processComeback();
            break;
        case CHARGING_REFINERY:
            this->harvestingTime = 0;
            return;
        default:
            break;
    this->harvestingTime = 0;
    this->chargingTime = 0;
    }    
}


void Harvester::addPointerToBuildings(std::map<uint16_t, Building*>* buildings) {
    this->buildings = buildings;
}

Harvester::~Harvester() {}
