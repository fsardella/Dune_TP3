#include "server_player.h"

Player::Player(const int& house, const std::string& playerName): playerName(playerName),
                                                                  house(house) {}

Player::~Player() {}



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
