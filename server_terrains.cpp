#include "server_terrains.h"

#include <iostream>

Terrain::Terrain() {}
Terrain::~Terrain() {}

void Terrain::occupySpace(coor_t coord, uint16_t id) {
    this->occupiedUnits[coord] = id;
}
void Terrain::freeSpace(coor_t coord) {
    this->occupiedUnits.erase(coord);
}

void Terrain::printDebug() {
    for (auto& tile : this->occupiedUnits) {
        std::cout << tile.first.first << ", " << tile.first.second << "; ";
    }
}

bool Terrain::canBuild() {
    return false;
}

uint16_t Terrain::getIdOfOccupant(coor_t coord) {
    if (!this->isOccupied(coord))
        return 0xFF;
    return this->occupiedUnits[coord];
}

bool Terrain::isBlocked() {
    return false;
}

bool Terrain::isOccupied(coor_t coord) {
    return (this->occupiedUnits.find(coord) != this->occupiedUnits.end());
}


Sand::Sand(): Terrain() {}
int Sand::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedForSand();
}
Sand::~Sand() {}

//debug
void Terrain::print() {
    std::cout << "░";
}

void Dune::print() {
    std::cout << "▒";
}

void Mount::print() {
    std::cout << "▓";
}

void Cliff::print() {
    std::cout << "█";
}

Rock::Rock(): Terrain() {}

void Rock::build(uint16_t building) {
    this->building_id = building;
    this->built = true;
}

bool Rock::canBuild() {
    if (this->built)
        return false;
    return (this->occupiedUnits.size() == 0);
}

bool Rock::isBlocked() {
    return this->built;
}

int Rock::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord) || this->isBlocked())
        return 0;
    return unit.getSpeedForSand();
}
Rock::~Rock() {}



Spice::Spice(u_int16_t quantity): Terrain(), quantity(quantity) {} 
int Spice::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedForSand();
}
Spice::~Spice() {}



Dune::Dune(): Terrain() {}
int Dune::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedForDune();
}
Dune::~Dune() {}


Mount::Mount(): Terrain() {}
int Mount::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedForMount();
}
Mount::~Mount() {}

Cliff::Cliff(): Terrain() {}
int Cliff::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedForCliff();
}

bool Cliff::isBlocked() {
    return true;
}

Cliff::~Cliff() {}
