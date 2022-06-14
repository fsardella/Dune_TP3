#include "server_player.h"

Player::Player(const int& house, const std::string& playerName): playerName(playerName),
                                                                  house(house) {}
Player::Player(): playerName(""),
                 house(-1) {
}



void Player::addUnit(int x, int y, TerrainMap& terr) {
    Unit* unit = new Vehicle(coor_t(y, x), terr);
    units.push_back(unit);
}

std::list<coor_t> Player::getUnits() {
    std::list<coor_t> result;
    for (Unit* unit: this->units) {
        result.push_back(unit->getPosition());
    }
    return result;
}

int Player::getHouse() {
    return this->house;
}

Player::~Player() {
    for (Unit* unit: this->units) {
        delete unit;
    }
}



Player::Player(Player&& other) : playerName(std::move(other.playerName)),
                                 house(other.house),
                                 units(std::move(other.units)) {}

Player& Player::operator=(Player&& other) {
    if (this == &other)
        return *this;
    this->house = other.house;
    this->playerName = std::move(other.playerName);
    this->units = std::move(other.units);
    return *this;
}
