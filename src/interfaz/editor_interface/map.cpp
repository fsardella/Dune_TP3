#include "map.h"

Map::Map() {}

void Map::setName(std::string& mapName) {
    this->name = mapName;
}

void Map::setWidth(int mapWidth) {
    this->width = mapWidth;
}

void Map::setHeight(int mapHeight) {
    this->height = mapHeight;
}

void Map::setNPlayers(int mapNPlayers) {
    this->nPlayers = mapNPlayers;
}

void Map::setIsNotNew() {
    this->isNew = false;
}

void Map::setMap(std::vector<std::vector<int>> map) { // posiblemente no ande
    this->map = map;
}

std::string Map::getName() {
    return this->name;
}

int Map::getWidth() {
    return this->width;
}

int Map::getHeight() {
    return this->height;
}

int Map::getNPlayers() {
    return this->nPlayers;
}

bool Map::getIsNew() {
    return this->isNew;
}

std::vector<std::vector<int>> Map::getMap() {
    return this->map; // posiblemente no ande
}

void Map::modifyMapAt(int row, int column, int id) {
    map[row][column] = id;
}

Map::Map(Map &&other) {
    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->nPlayers = other.nPlayers;
    this->map = other.map; // posiblemente haya que poner un std::move y asi no agregar lo del otro
    other.name = nullptr;
    other.width = 0;
    other.height = 0;
    other.nPlayers = 0;
}

Map &Map::operator=(Map &&other)  {
    if (this == &other) {
        return *this;
    }

    // aca puede ir algo mas

    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->nPlayers = other.nPlayers;
    this->map = other.map; // posiblemente haya que poner un std::move y asi no agregar lo del otro
    other.name = nullptr;
    other.width = 0;
    other.height = 0;
    other.nPlayers = 0;

    return *this;
}
