#include "server_player.h"

#include <iostream>

Player::Player(const int& house, const std::string& playerName,
               coor_t baseCoords): playerName(playerName),
                                   house(house),
                                   base(Base(baseCoords, playerName)){}



#define CHUNKSIZE 8

Player::Player(): playerName(""),
                 house(-1),
                 base(Base(coor_t(0,0), "")) {
}


void Player::buildBase(TerrainMap& terr, uint16_t id) {
    this->base.build(terr, this->base.getPosition(), id);
}

void Player::setID(uint8_t newID) {
    this->playerID = newID;
}

bool Player::hasUnit(uint16_t unitID) {
    return (this->units.find(unitID) != this->units.end());
}

bool Player::hasBuilding(uint16_t buildingID) {
    if (buildingID == this->playerID) // la base!
        return true;
    return (this->buildings.find(buildingID) != this->buildings.end());
}

uint8_t Player::getID() {
    return this->playerID;
}

coor_t Player::getBaseCoords() {
    return this->base.getPosition();
}

uint32_t Player::getMoney() {
    return this->money;
}

int32_t Player::getEnergy() {
    return this->energy;
}

void Player::kill(std::list<Command>& events) {
    this->base.destroy(events);
}

uint32_t Player::getPriceOfCreation(uint8_t type) {
    // lo implementaria en static methods, pero asi no se podria
    // usar el config...
    switch (type) {
        case TRIKE:
            return 100;
        case RAIDER:
            return 100;
        case TANK:
            return 300;
        case HARVESTER:
            return 300;
        case DEVIATOR:
            return 400;
        case DEVASTATOR:
            return 400;
        case SONIC_TANK:
            return 300;
        case LIGHT_INFANTRY:
            return 50;
        case HEAVY_INFANTRY:
            return 70;
        case SARDAUKAR:
            return 100;
        case FREMEN:
            return 100;
        case LIGHT_FACTORY:
            return 800;
        case HEAVY_FACTORY:
            return 1500;
        case PALACE:
            return 2000;
        case REFINERY:
            return 500;
        case SILO:
            return 200;
        case WINDTRAP:
            return 800;
        case BARRACK:
            return 300;
    }
    return 0;
}

uint8_t Player::getUnitFactor(uint8_t type) {
    uint8_t factoryMultiplier = 1;
    switch (type) {
        case TRIKE:
            factoryMultiplier = this->cantLightFactories;
            break;
        case HARVESTER:
            factoryMultiplier = this->cantHeavyFactories;
            break;
    }
    return (5 + this->getEnergyPenalization()) * factoryMultiplier;
}

coor_t Player::getUnitDir(uint8_t type, TerrainMap& terr) {
    coor_t ret(0,0); // Imposible que esta sea una dir valida
    bool ended = false;
    for (auto& iterat : this->buildings) {
        Building* building = iterat.second;
        switch (type) {
            case TRIKE:
                std::cout << "case trike\n";
                if (!building->isLightFactory())
                    continue;
                break;
            case HARVESTER:
                if (!building->isHeavyFactory())
                    continue;
                break;
        }
        std::cout << "sigo con la iteración\n";
        coor_t buildingPos = building->getPosition();
        std::cout << buildingPos.first << " y " << buildingPos.second << std::endl;
        uint16_t i = buildingPos.first + building->getSize().first * CHUNKSIZE + 1;
        std::cout << i << std::endl;
        for (uint16_t j = buildingPos.second;
             j < buildingPos.second + building->getSize().second * CHUNKSIZE;
             j++) {
            coor_t act(i, j);
            std::cout << "i " << i << " j " << j << std::endl;
            if (terr.isOccupied(act) || terr.isBlocked(act))
                continue;
            std::cout << "cambio rect\n";
            ret = act;
            ended = true;
            break;
        }
        if (ended)
            break;
    }
    return ret;
}

Unit* Player::getUnit(uint16_t unitID) {
    if (!this->hasUnit(unitID) || this->units[unitID]->isDead())
        return nullptr;
    return this->units[unitID];
}

Building* Player::getBuilding(uint16_t buildingID) { 
    if (!this->hasBuilding(buildingID) ||
        !this->buildings[buildingID]->destroyed())
        return nullptr;
    if (buildingID == this->playerID)
        return &this->base;
    return this->buildings[buildingID];
}


bool Player::chargeMoney(uint8_t type) {
    if (this->getPriceOfCreation(type) > this->money)
        return false;
    this->money -= this->getPriceOfCreation(type);
    return true;
}

void Player::addUnit(Unit* unit) {
    this->units[unit->getID()] = unit;
    if (unit->isHarvester())
        unit->addPointerToBuildings(&this->buildings);
}


void Player::moveUnit(uint16_t unitID, coor_t coor) {
    if (!this->hasUnit(unitID) || this->units[unitID]->isDead())
        return;
    this->units[unitID]->setDest(coor);
}

void Player::updateUnits(std::list<Command>& events) {
    for (auto& unit : this->units) {
        if (!unit.second->isDead())
            unit.second->update(events);
    } 
}

uint16_t Player::getEnergyPenalization() {
    if (this->energy >= 0)
        return 0;
    if (this->energy < -2500)
        return -5;
    return this->energy / 500 - 1;
}

uint16_t Player::getConstructionDelta() {
    return 5 + this->getEnergyPenalization();
}

void Player::updateBuildings() {
    this->cantHeavyFactories = 0;
    this->cantLightFactories = 0;
    this->energy = 0;
    this->moneyCapacity = 0;
    for (auto& building : this->buildings) {
        if (building.second->destroyed())
            continue;
        this->cantLightFactories += (int)building.second->isLightFactory();
        this->cantHeavyFactories += (int)building.second->isHeavyFactory();
        this->energy += building.second->getEnergy();
        this->moneyCapacity += building.second->getMoneyCapacity();
    } 
    for (auto& building : this->buildings) {
        if (building.second->destroyed())
            continue;
        this->money += building.second->gatherMoney(this->money,
                                                    this->moneyCapacity);
    }
    if (this->buildingBirthing != nullptr)
        this->buildingBirthing->update(this->getConstructionDelta());
}

uint16_t manhattanDistance(coor_t dest, coor_t other) {
    return (uint16_t)(abs((int)dest.first - (int)other.first)
                    + abs((int)other.second - (int)other.second));
}

bool Player::isBlockInRange(coor_t blockCoord) {
    coor_t toCompareBlock, toCompareSize;
    toCompareBlock = coor_t(this->base.getPosition().first / CHUNKSIZE,
                            this->base.getPosition().second / CHUNKSIZE);
    toCompareSize = this->base.getSize();
    for (uint16_t i = toCompareBlock.first;
        i < toCompareBlock.first + toCompareSize.first;
        i++) {
        for (uint16_t j = toCompareBlock.second;
            j < toCompareBlock.second + toCompareSize.second;
            j++) {
            if (manhattanDistance(coor_t(i, j), blockCoord) <= 5) 
                return true;
        }
    }

    for (auto& building : this->buildings) {
        toCompareBlock = coor_t(building.second->getPosition().first / CHUNKSIZE,
                                building.second->getPosition().second / CHUNKSIZE);
        toCompareSize = building.second->getSize();
        for (uint16_t i = toCompareBlock.first;
         i < toCompareBlock.first + toCompareSize.first;
         i++) {
            for (uint16_t j = toCompareBlock.second;
             j < toCompareBlock.second + toCompareSize.second;
             j++) {
                if (manhattanDistance(coor_t(i, j), blockCoord) <= 5) 
                    return true;
            }
        }
    }
    return false;
}

bool Player::isBuildingInRange(Building* toBuild, uint16_t x, uint16_t y) {
    std::cout << "X ERA " << x << " y Y " << y << std::endl;
    coor_t toBuildBlock(y / CHUNKSIZE,
                        x / CHUNKSIZE);
    coor_t toBuildSize = toBuild->getSize();
    for (uint16_t i = toBuildBlock.first;
         i < toBuildBlock.first + toBuildSize.first;
         i++) {
        for (uint16_t j = toBuildBlock.second;
             j < toBuildBlock.second + toBuildSize.second;
             j++) {
            if (this->isBlockInRange(coor_t(i, j))) {
                std::cout << "1: return true\n";
                return true; }
        }            
    }
    std::cout << "1: return false\n";
    return false;
}

void Player::createBuilding(uint8_t type) {
    if (this->buildingBirthing != nullptr)
        return;
    if (!chargeMoney(type))
        return;
    this->buildingBirthing = Building::newBuilding(type, this->playerName);
}

uint16_t Player::addBuilding(uint16_t x, uint16_t y, TerrainMap& terr,
                         uint16_t id) {
    uint16_t ret = 0xFFFF;
    if (this->buildingBirthing == nullptr)
        return ret;
    if (!this->isBuildingInRange(this->buildingBirthing, x, y)
        || !this->buildingBirthing->canBuild(terr, coor_t(y, x))) {
        return ret;
    }
    this->buildingBirthing->build(terr, coor_t(y, x), id);
    ret = this->buildingBirthing->getType();
    this->buildings[id] = this->buildingBirthing;
    this->buildingBirthing = nullptr;
    return ret;
}

std::list<UnitData> Player::getUnits() {
    std::list<UnitData> result;
    for (auto&  unit: this->units) {
        UnitData unitData(unit.second->getPosition(), (uint8_t)this->house,
                    unit.second->getDir(), unit.first, unit.second->getType());
        result.push_back(unitData);
    }
    return result;
}

std::pair<uint8_t, uint8_t> Player::getBuildingInfo() {
    if (this->buildingBirthing == nullptr)
        return std::pair<uint8_t, uint8_t>(0xFF, 0xFF);
    return std::pair<uint8_t, uint8_t>(this->buildingBirthing->getType(),
                                       this->buildingBirthing->getCompletion());
}

int Player::getHouse() {
    return this->house;
}


bool Player::hasLost() {
    return this->base.destroyed();
}

void Player::cleanCorpses(std::map<uint16_t, std::string>& unitIDs,
                      std::map<uint16_t, std::string>& buildingIDs,
                      std::list<Command>& events) {
    if (this->hasLost() && !this->alreadyLost) {
        this->alreadyLost = true;
        for (auto& u : this->units)
            u.second->kill(events);
        for (auto& b : this->buildings)
            b.second->destroy(events);
    }
    auto unitIT = this->units.begin();
    while (unitIT != this->units.end()) {
        if (unitIT->second->canBeCleaned()) {
            unitIDs.erase(unitIT->second->getID());
            delete unitIT->second;
            unitIT = this->units.erase(unitIT);
        } else {
            unitIT++;
        }
    }
    auto buildingIT = this->buildings.begin();
    while (buildingIT != this->buildings.end()) {
        if (buildingIT->second->canBeCleaned()) {
            buildingIDs.erase(buildingIT->second->getID());
            delete buildingIT->second;
            buildingIT = this->buildings.erase(buildingIT);
        } else {
            buildingIT++;
        }
    }
}


bool Player::canBeCleaned() {
    return (this->hasLost() && this->units.size() == 0 && this->buildings.size() == 0);
}

Player::~Player() {
    for (auto& unit: this->units) {
        delete unit.second;
    }
    for (auto& building: this->buildings) {
        delete building.second;
    }
    if (this->buildingBirthing != nullptr)
        delete buildingBirthing;
}



Player::Player(Player&& other) : playerName(std::move(other.playerName)),
                                 house(other.house),
                                 units(std::move(other.units)),
                                 base(std::move(other.base)),
                                 playerID(other.playerID),
                                 buildingBirthing(other.buildingBirthing),
                                 cantLightFactories(other.cantLightFactories),
                                 cantHeavyFactories(other.cantHeavyFactories),
                                 energy(other.energy),
                                 moneyCapacity(other.moneyCapacity),
                                 money(other.money),
                                 buildings(std::move(other.buildings)),
                                 alreadyLost(other.alreadyLost) {}

Player& Player::operator=(Player&& other) {
    if (this == &other)
        return *this;
    this->house = other.house;
    this->playerID = other.playerID;
    this->playerName = std::move(other.playerName);
    this->units = std::move(other.units);
    this->base = std::move(other.base);
    this->buildingBirthing = other.buildingBirthing;
    this->cantLightFactories = other.cantLightFactories;
    this->cantHeavyFactories = other.cantHeavyFactories;
    this->energy = other.energy;
    this->moneyCapacity = other.moneyCapacity;
    this->money = other.money;
    this->buildings = std::move(other.buildings);
    this->alreadyLost = other.alreadyLost;

    return *this;
}
