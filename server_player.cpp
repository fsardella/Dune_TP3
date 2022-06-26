#include "server_player.h"

Player::Player(const int& house, const std::string& playerName,
               coor_t baseCoords): playerName(playerName),
                                   house(house),
                                   base(Base(baseCoords)){}



Player::Player(): playerName(""),
                 house(-1),
                 base(Base(coor_t(0,0))) {
}


void Player::buildBase(TerrainMap& terr, uint16_t id) {
    terr.build(this->base.getPosition(), this->base.getSize(), id);
}


coor_t Player::getBaseCoords() {
    return this->base.getPosition();
}

void Player::addUnit(int x, int y, TerrainMap& terr) {
    Unit* unit = new Vehicle(coor_t(y, x), terr);
    units[units.size()] = unit;
}

std::list<UnitData> Player::getUnits() {
    std::list<UnitData> result;
    for (auto&  unit: this->units) {
        UnitData unitData(unit.second->getPosition(), (uint8_t)this->house);
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
