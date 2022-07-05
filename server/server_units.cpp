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
                                speed(speed) {
    terr.addUnit(coor, this);                                   
}

Infantry::Infantry(coor_t coor, TerrainMap& terr, uint16_t life,
           Weapon* weapon, uint16_t id, uint16_t speed, std::string owner):
                            Unit(coor, terr, life,
                                 weapon, id, speed, owner) {}

Vehicle::Vehicle(coor_t coor, TerrainMap& terr, uint16_t life, Weapon* weapon, 
                 uint16_t id, uint16_t speed, std::string owner):
                            Unit(coor, terr, life,
                                 weapon, id, speed, owner) {}


coor_t Unit::getPosition() {
    return this->moveAlgorithm.getPosition();
}

uint8_t Unit::getDir() {
    if (this->state == IDLE)
        return 4; // El IDLE del astar
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
    this->actDest = coor_t(attackedPos.first + attackedDims.first * CHUNKSIZE + 1,
                           attackedPos.second + attackedDims.second * CHUNKSIZE / 2);
}

void Unit::damage(uint16_t dam) {
    if (this->actualLife <= dam) {
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
    if (this->buildingObjv != nullptr)
        this->buildingObjv->stopWatching();
    if (this->unitObjv != nullptr)
        this->unitObjv->stopWatching();
    this->moveAlgorithm.eraseUnitFromMap();
}

void Unit::kill(std::list<Command>& events) {
    if (!this->isDead()) {
        this->die();
        Command dead;
        dead.add8bitsMessage(UNIT_ATTACKED);
        dead.add16bitsMessage(0xFFFF);
        dead.add16bitsMessage(this->id);
        dead.add16bitsMessage(0);
        dead.add16bitsMessage(this->totalLife);
        dead.add8bitsMessage(0xFF);
        events.push_back(dead);
    }
    this->actualLife = 0;
}

void Unit::processMove() {
    //this->moveAlgorithm.print();
    this->weapon->stopAttack();
    this->speedAcum += this->speed * this->moveAlgorithm.getSpeedMod();
    uint8_t steps = this->speedAcum / 30;
    this->speedAcum = this->speedAcum % 30;
    for (uint8_t i = 0; i < steps; i++) {
        bool ret = this->moveAlgorithm.processMove(this->actDest);
        if (ret) {
            if (this->actDest == this->moveAlgorithm.getPosition()) {
                std::cout << "ENDED MOVE!";
                this->state = IDLE;
                break;
            }
        } else {
            std::cout << "COULDNT FIND PATH\n";
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
            attack.add8bitsMessage(UNIT_ATTACKED);
            attack.setType(UNIT_ATTACKED);
            attack.add16bitsMessage(this->id);
            attack.add16bitsMessage(this->unitObjv->getID());
            attack.add16bitsMessage(this->unitObjv->getActualLife());
            attack.add16bitsMessage(this->unitObjv->getTotalLife());
            attack.add8bitsMessage(this->weapon->getType());
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
            attack.add8bitsMessage(BUILDING_ATTACKED);
            attack.setType(BUILDING_ATTACKED);
            attack.add16bitsMessage(this->id);
            attack.add16bitsMessage(this->buildingObjv->getID());
            attack.add16bitsMessage(this->buildingObjv->getActualLife());
            attack.add16bitsMessage(this->buildingObjv->getTotalLife());
            attack.add8bitsMessage(this->weapon->getType());
            events.push_back(attack);
        }
    } else {
        this->processMove();
    }
}

void Unit::processIdle(std::list<Command>& events) {
    Unit* tempObjv = this->weapon->scout(this);
    if (tempObjv == nullptr || tempObjv->isDead()) {
        this->weapon->stopAttack();
        return;
    }
    this->weapon->startAttack();
    if (this->weapon->attack(tempObjv)) {
        Command attack;
        attack.add8bitsMessage(UNIT_ATTACKED);
        attack.setType(UNIT_ATTACKED);
        attack.add16bitsMessage(this->id);
        attack.add16bitsMessage(tempObjv->getID());
        attack.add16bitsMessage(tempObjv->getActualLife());
        attack.add16bitsMessage(tempObjv->getTotalLife());
        attack.add8bitsMessage(this->weapon->getType());
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
            this->processMove();
            break;
        default:
            break;
    }
}


void Unit::watch() {
    this->watchers++;
}


void Unit::stopWatching() {
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

uint16_t Infantry::getDamageFor(Weapon* weapon) {
    return weapon->getDamageModForInfantry();
}


Infantry::~Infantry() {}


LightInfantry::LightInfantry(coor_t coor, TerrainMap& terr, uint16_t id,
                                std::string owner, Config* c):
                                        Infantry(coor, terr, c->LIGHT_INFANTRY_LIFE, 
                                                new AssaultRifle(terr,
                                                c->LIGHT_INFANTRY_RANGE, c),
                                                id, c->LIGHT_INFANTRY_SPEED, owner) {}

uint8_t LightInfantry::getType() {
    return LIGHT_INFANTRY;
}

LightInfantry::~LightInfantry() {}




HeavyInfantry::HeavyInfantry(coor_t coor, TerrainMap& terr, uint16_t id,
                                std::string owner, Config* c):
                                        Infantry(coor, terr, c->HEAVY_INFANTRY_LIFE, 
                                                new RocketLauncher(terr,
                                                c->HEAVY_INFANTRY_RANGE, c),
                                                id, c->HEAVY_INFANTRY_SPEED, owner) {}

uint8_t HeavyInfantry::getType() {
    return HEAVY_INFANTRY;
}

HeavyInfantry::~HeavyInfantry() {}




Fremen::Fremen(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c):        Infantry(coor, terr, c->FREMEN_LIFE, 
                    /*DOUBLE HANDED*/ new AssaultRifle(terr,
                                      c->FREMEN_RANGE, c),
                                      id, c->FREMEN_SPEED, owner) {}

uint8_t Fremen::getType() {
    return FREMEN;
}
    
Fremen::~Fremen() {}



Sardaukar::Sardaukar(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c):    Infantry(coor, terr, c->SARDAUKAR_LIFE, 
            /*DOUBLE HANDED*/     new RocketLauncher(terr,
                                  c->SARDAUKAR_RANGE, c),
                                  id, c->SARDAUKAR_SPEED, owner) {}
          

uint8_t Sardaukar::getType() {
    return SARDAUKAR;        
}

Sardaukar::~Sardaukar() {}

int Vehicle::getSpeedWeightForMount() {
    return WALL;
}

uint16_t Vehicle::getDamageFor(Weapon* weapon) {
    return weapon->getDamageModForVehicle();
}

Vehicle::~Vehicle() {}



Trike::Trike(coor_t coor, TerrainMap& terr, uint16_t id,
                     std::string owner, Config* c) :
                                        Vehicle(coor, terr, c->TRIKE_LIFE, 
                                                new AssaultRifle(terr,
                                                c->TRIKE_RANGE, c),
                                                id, c->TRIKE_SPEED, owner) {}


uint8_t Trike::getType() {
    return TRIKE;
}

Trike::~Trike() {}




Raider::Raider(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
                Config* c): Vehicle(coor, terr, c->RAIDER_LIFE, 
                                    new TTCannon(terr,
                                        c->RAIDER_RANGE, c),
                                    id, c->RAIDER_SPEED, owner) {}
uint8_t Raider::getType() {
    return RAIDER;
}

Raider::~Raider() {}



Tank::Tank(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c) : Vehicle(coor, terr, c->TANK_LIFE, 
                                    new Cannon(terr,
                                        c->TANK_RANGE, c),
                                    id, c->TANK_SPEED, owner) {}
          
uint8_t Tank::getType() {
    return TANK;
}

Tank::~Tank() {}


Harvester::Harvester(coor_t coor, TerrainMap& terr, uint16_t id,
                     std::string owner, Config* c): 
                                          Vehicle(coor, terr, c->HARVESTER_LIFE,
/*Tiene un arma dummy */                  new AssaultRifle(terr, 0, c),
/* para evitar segfault*/                 id, c->HARVESTER_SPEED, owner),
                                          menageCap(c->HARVESTER_HARVEST_LIMIT),
                                          harvestTimeLimit(c->HARVESTER_HARVESTTIME),
                                          chargingTimeLimit(c->HARVESTER_RECHARGETIME),
                                          range(c->HARVESTER_RANGE),
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
                newDest = coor_t(pos.first + dims.first * CHUNKSIZE,
                            pos.second + dims.second * CHUNKSIZE / 2);
                Vehicle::setDest(newDest);
                return true;
            }
        }
        return false;
    }
    coor_t pos = this->ref->getPosition();
    coor_t dims = this->ref->getSize();
    newDest = coor_t(pos.first + dims.first * CHUNKSIZE,
                    pos.second + dims.second * CHUNKSIZE / 2);
    Vehicle::setDest(newDest);
    return true;
}

void Harvester::processHarvest() {
    if (this->getPosition() != this->actHarvestDest) {
        this->processMove();
        this->state = HARVESTING;
        return;
    }
    if (!this->terr.hasMenage(this->actHarvestDest)) {
        this->harvestingTime = 0;
        this->scoutForMenage();
        return;
    }
    this->harvestingTime += 1;
    if (this->harvestingTime >= this->harvestTimeLimit) {
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
    for (int i = -CHUNKSIZE * this->range; i <= CHUNKSIZE * this->range; i += CHUNKSIZE) {
        for (int j = -CHUNKSIZE * this->range; j <= CHUNKSIZE * this->range; j += CHUNKSIZE) {
            if (abs(i / CHUNKSIZE) + abs(j / CHUNKSIZE) > this->range) {
                continue;
            }
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
    if (this->isNextToRefinery()) {
        if (this->actMenage == 0)
            this->state = IDLE;
        else
            this->state = CHARGING_REFINERY;
    } else {
        this->processMove();
        this->state = GOING_TO_REFINERY;
    }
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
    if (this->chargingTime >= this->chargingTimeLimit) {
        this->chargingTime = 0;
        this->ref->rechargeMoney(this->actMenage);
        this->actMenage = 0;
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
            this->processCharging();
            this->harvestingTime = 0;
            return;
        default:
            break;
    this->harvestingTime = 0;
    this->chargingTime = 0;
    }    
}

void Harvester::die() {
    if (this->ref != nullptr)
        this->ref->stopWatching();
    Vehicle::die();
}

void Harvester::addPointerToBuildings(std::map<uint16_t, Building*>* buildings) {
    this->buildings = buildings;
}

Harvester::~Harvester() {}




Deviator::Deviator(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c) : Vehicle(coor, terr, c->DEVIATOR_LIFE, 
  /*new DeviatorLauncher*/     new RocketLauncher(terr,
                                    c->DEVIATOR_RANGE, c),
                               id, c->DEVIATOR_SPEED, owner) {}

uint8_t Deviator::getType() {
    return DEVIATOR;
}

Deviator::~Deviator() {}



Devastator::Devastator(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c, std::list<Command>& events):
                            Vehicle(coor, terr, c->DEVASTATOR_LIFE, 
                                    new PlasmaCannon(terr,
                                    c->DEVASTATOR_RANGE, c),
                                    id, c->DEVASTATOR_SPEED, owner),
                                    explosionDamage(c->DEVASTATOR_EXPLOSION),
                                    terr(terr),
                                    explosionBroadcaster(events) {}

uint8_t Devastator::getType() {
    return DEVASTATOR;
}


void Devastator::die() {
    std::list<Unit*> exploded = this->terr.getAllUnits(this->getPosition());
    for (Unit* rip : exploded) {
        if (rip->getID() == this->getID())
            continue;
        rip->damage(this->explosionDamage);
        Command expl;
        expl.add8bitsMessage(UNIT_ATTACKED);
        expl.add16bitsMessage(0xFFFF);
        expl.add16bitsMessage(rip->getID());
        expl.add16bitsMessage(rip->getActualLife());
        expl.add16bitsMessage(rip->getTotalLife());
        expl.add8bitsMessage(0xFF);
        this->explosionBroadcaster.push_back(expl);
    }
    Vehicle::die();
}

Devastator::~Devastator() {}



SonicTank::SonicTank(coor_t coor, TerrainMap& terr, uint16_t id, std::string owner,
          Config* c) :  Vehicle(coor, terr, c->SONIC_TANK_LIFE, 
                                new SoundWaves(terr,
                                c->SONIC_TANK_RANGE, c),
                                id, c->SONIC_TANK_SPEED, owner) {}


uint8_t SonicTank::getType() {
    return SONIC_TANK;
}


SonicTank::~SonicTank() {}


