#include "server_buildings.h"

#include <iostream>

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



Building::Building(coor_t size, uint16_t totalLife, uint16_t buildingTime,
                   int32_t energy, std::string owner):
                   size(size),
                   actualLife(totalLife),
                   totalLife(totalLife),
                   buildingTime(buildingTime),
                   energy(energy),
                   owner(owner) {}

coor_t Building::getPosition() {
    return this->position;
}

coor_t Building::getSize() {
    return this->size;
}

uint16_t Building::getID() {
    return this->buildingID;
}

std::string Building::getOwner() {
    return this->owner;   
}

uint32_t Building::getMoneyCapacity() {
    return 0;
}

uint32_t Building::gatherMoney(uint32_t actualMoney, uint32_t moneyCapacity) {
    return 0;
}

Building* Building::newBuilding(uint8_t type, std::string owner, Config* c) {
    switch (type) {
        case LIGHT_FACTORY:
            return new LightFactory(owner, c);
        case HEAVY_FACTORY:
            return new HeavyFactory(owner, c);
        case REFINERY:
            return new Refinery(owner, c);
        case WINDTRAP:
            return new WindTrap(owner, c);
        default:
            return nullptr;
    }
}

bool Building::isLightFactory() {
    return false;
}

bool Building::isHeavyFactory() {
    return false;
}

bool Building::isRefinery() {
    return false;
}

uint16_t Building::getActualLife() {
    return this->actualLife;
}

uint16_t Building::getTotalLife() {
    return this->totalLife;
}

void Building::update(uint16_t constructionTime) {
    if (this->buildingTime <= this->actualTime)
        return;
    this->actualTime += constructionTime;
}

uint8_t Building::getCompletion() {
    if (this->actualTime >= this->buildingTime)
        return 100;
    return (uint8_t) ((this->actualTime * 100) / this->buildingTime);
}


bool Building::canBuild(TerrainMap& terr, coor_t position) {
    if (this->buildingTime > this->actualTime)
        return false;
    return terr.canBuild(position, this->size);
}

void Building::build(TerrainMap& terr, coor_t position, uint16_t id) {
    this->buildingID = id;
    this->position = coor_t(position.first / CHUNKSIZE * CHUNKSIZE,
                            position.second / CHUNKSIZE * CHUNKSIZE);
    this->terrain = &terr;
    return terr.build(this->position, this);
}

void Building::eraseFromMap() {
    this->terrain->eraseBuildingFromMap(this->position, this->size);
}

void Building::attack(uint16_t damage) {
    if (this->actualLife <= damage) {
        if (!this->destroyed())
            this->eraseFromMap();
        this->actualLife = 0;
    } else {
        this->actualLife -= damage;
    }
}

void Building::destroy(std::list<Command>& events) {
    if (!this->destroyed()) {
        this->eraseFromMap();
        Command dead;
        dead.add8BytesMessage(BUILDING_ATTACKED);
        dead.add16BytesMessage(0xFFFF);
        dead.add16BytesMessage(this->buildingID);
        dead.add16BytesMessage(0);
        dead.add16BytesMessage(this->totalLife);
        events.push_back(dead);
    }
    this->actualLife = 0;
}
    
bool Building::destroyed() {
    return (this->actualLife == 0);
}

void Building::watch() {
    this->watchers++;    
}

void Building::stopWatching() {
    this->watchers--;
}

int32_t Building::getEnergy() {
    return this->energy;
}

bool Building::canBeCleaned() {
    if (!this->destroyed())
        return false;
    return (this->watchers <= 0);
}


Building::~Building() {}



Base::Base(coor_t position, std::string owner, Config* c):
        Building(coor_t(3, 3), c->BASE_LIFE, 0, 0, owner) {
    this->position = position;
}


Base::Base(): Building(coor_t(0, 0), 0, 0, 0, "") {}

uint16_t Base::getType() {
    return BASE;
}

Base::~Base() {}


LightFactory::LightFactory(std::string owner, Config* c):
                Building(coor_t(3, 3), c->LIGHT_FACTORY_LIFE,
                        c->LIGHT_FACTORY_CTIME, c->LIGHT_FACTORY_ENERGY,
                        owner) {} 

bool LightFactory::isLightFactory() {
    return true;
}

uint16_t LightFactory::getType() {
    return LIGHT_FACTORY;
}

LightFactory::~LightFactory() {}

HeavyFactory::HeavyFactory(std::string owner, Config* c):
                Building(coor_t(4, 4), c->HEAVY_FACTORY_LIFE,
                c->HEAVY_FACTORY_CTIME, c->HEAVY_FACTORY_ENERGY, owner) {} 

bool HeavyFactory::isHeavyFactory() {
    return true;
}

uint16_t HeavyFactory::getType() {
    return HEAVY_FACTORY;
}


HeavyFactory::~HeavyFactory() {}



Refinery::Refinery(std::string owner, Config* c):
                        Building(coor_t(3, 3), c->REFINERY_LIFE,
                        c->REFINERY_CTIME, c->REFINERY_ENERGY, owner),
                        moneyCap(c->REFINERY_CAPACITY) {}

bool Refinery::isRefinery() {
    return true;
}

uint32_t Refinery::gatherMoney(uint32_t actualMoney, uint32_t moneyCapacity) {
    uint32_t ret = this->money;
    this->money = 0;
    if (ret + actualMoney > moneyCapacity) {
        if (actualMoney < moneyCapacity)
            return moneyCapacity - actualMoney;
        else
            return 0;
        }
    return ret;
}

void Refinery::rechargeMoney(uint32_t menage) {
    this->money += menage;
}


uint16_t Refinery::getType() {
    return REFINERY;
}

uint32_t Refinery::getMoneyCapacity() {
    return this->moneyCap;
}


Refinery::~Refinery() {}


WindTrap::WindTrap(std::string owner, Config* c):
                        Building(coor_t(3, 3), c->AIR_TRAP_LIFE,
                        c->AIR_TRAP_CTIME, c->AIR_TRAP_ENERGY, owner) {}


uint16_t WindTrap::getType() {
    return WINDTRAP;
}

WindTrap::~WindTrap() {}
