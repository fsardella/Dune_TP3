#include "server_player.h"

Player::Player(const int& house, const std::string& playerName,
               coor_t baseCoords): playerName(playerName),
                                   house(house),
                                   base(Base(baseCoords)){}



#define CHUNKSIZE 8
#define TRIKE 0

Player::Player(): playerName(""),
                 house(-1),
                 base(Base(coor_t(0,0))) {
}


void Player::buildBase(TerrainMap& terr, uint16_t id) {
    terr.build(this->base.getPosition(), this->base.getSize(), id);
}

void Player::setID(uint8_t newID) {
    this->playerID = newID;
}

bool Player::hasUnit(uint16_t unitID) {
    return (this->units.find(unitID) != this->units.end());
}

bool Player::hasBuilding(uint16_t buildingID) {
    return (this->buildings.find(buildingID) != this->buildings.end());
}

uint8_t Player::getID() {
    return this->playerID;
}

coor_t Player::getBaseCoords() {
    return this->base.getPosition();
}

uint8_t Player::getUnitFactor(uint8_t type) {
    switch (type) {
        case TRIKE:
            return this->cantLightFactories;
    }
    return 0;
}

coor_t Player::getUnitDir(uint8_t type, TerrainMap& terr) {
    coor_t ret(0,0); // Imposible que esta sea una dir valida
    bool ended = false;
    for (auto& iterat : this->buildings) {
        Building* building = iterat.second;
        switch (type) {
            case TRIKE:
                if (!building->isLightFactory())
                    continue;
        }
        coor_t buildingPos = building->getPosition();
        uint16_t i = buildingPos.first + building->getSize().first;
        for (uint16_t j = buildingPos.second;
             j < building->getSize().second; j++) {
            coor_t act(i, j);
            if (terr.isOccupied(act))
                continue;
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
    if (!this->hasUnit(unitID))
        return nullptr;
    return this->units[unitID];
}

Building* Player::getBuilding(uint16_t buildingID) { 
    if (!this->hasBuilding(buildingID))
        return nullptr;
    return this->buildings[buildingID];
}


void Player::addUnit(Unit* unit, uint8_t id) {
    this->units[id] = unit;
}

enum buildingTypes {
    BASE = 0,
    LIGHT_FACTORY
};

Building* newBuilding(uint8_t type, uint16_t x, uint16_t y) {
    switch (type) {
        case LIGHT_FACTORY:
            return new LightFactory(coor_t(y, x));
        default:
            return NULL;
    }
}

void Player::moveUnit(uint16_t unitID, coor_t coor) {
    if (!this->hasUnit(unitID))
        return;
    this->units[unitID]->setDest(coor);
}

void Player::updateUnits() {
    for (auto& unit : this->units) {
        unit.second->update();
    } 
}

uint16_t manhattanDistance(coor_t dest, coor_t other) {
    return (uint16_t)(abs((int)dest.first - (int)other.first)
                    + abs((int)other.second - (int)other.second));
}

bool Player::isBlockInRange(coor_t blockCoord) {
    coor_t toCompareBlock, toCompareSize;
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

bool Player::isBuildingInRange(Building* toBuild) {
    coor_t toBuildBlock(toBuild->getPosition().first / CHUNKSIZE,
                        toBuild->getPosition().second / CHUNKSIZE);
    coor_t toBuildSize = toBuild->getSize();
    for (uint16_t i = toBuildBlock.first;
         i < toBuildBlock.first + toBuildSize.first;
         i++) {
        for (uint16_t j = toBuildBlock.second;
             j < toBuildBlock.second + toBuildSize.second;
             j++) {
            if (this->isBlockInRange(coor_t(i, j)))
                return true;
        }            
    }
    return false;
}

void Player::addSpecialBuilding(uint8_t type) {
    switch (type) {
        case LIGHT_FACTORY:
            this->cantLightFactories++;
            return;
        default:
            return;
    }
}

bool Player::addBuilding(uint8_t type, uint16_t x, uint16_t y, TerrainMap& terr,
                         uint16_t id) {
    Building* toBuild = newBuilding(type, x, y);
    if (!this->isBuildingInRange(toBuild) || !toBuild->canBuild(terr)) {
        delete toBuild;
        return false;   
    }
    toBuild->build(terr, id);
    addSpecialBuilding(type);
    this->buildings[id] = toBuild;
    return true;
}

std::list<UnitData> Player::getUnits() {
    std::list<UnitData> result;
    for (auto&  unit: this->units) {
        UnitData unitData(unit.second->getPosition(), (uint8_t)this->house,
                          unit.second->getDir(), unit.first);
        result.push_back(unitData);
    }
    return result;
}

int Player::getHouse() {
    return this->house;
}

Player::~Player() {
    for (auto& unit: this->units) {
        delete unit.second;
    }
    for (auto& building: this->buildings) {
        delete building.second;
    }
}



Player::Player(Player&& other) : playerName(std::move(other.playerName)),
                                 house(other.house),
                                 units(std::move(other.units)),
                                 base(std::move(other.base)){}

Player& Player::operator=(Player&& other) {
    if (this == &other)
        return *this;
    this->house = other.house;
    this->playerName = std::move(other.playerName);
    this->units = std::move(other.units);
    this->base = std::move(other.base);
    return *this;
}
