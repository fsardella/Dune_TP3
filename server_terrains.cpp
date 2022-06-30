#include "server_terrains.h"

#include <iostream>

Terrain::Terrain() {}
Terrain::~Terrain() {}

void Terrain::occupySpace(coor_t coord, Unit* unit) {
    this->occupiedUnits[coord] = unit;
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

Unit* Terrain::getOccupant(coor_t coord) {
    if (!this->isOccupied(coord))
        return nullptr;
    return this->occupiedUnits[coord];
}

void Terrain::getAllOccupants(std::list<Unit*>& ret) {
    for (auto& tile : this->occupiedUnits) {
        ret.push_back(tile.second);
    }
}

Building* Terrain::getBuilding() {
    return nullptr;
}

bool Terrain::isBlocked() {
    return false;
}

bool Terrain::isOccupied(coor_t coord) {
    return (this->occupiedUnits.find(coord) != this->occupiedUnits.end());
}


Sand::Sand(): Terrain() {}
int Sand::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedWeightForSand();
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

void Rock::build(Building* newBuilding) {
    this->building = newBuilding;
}

bool Rock::canBuild() {
    if (this->isBlocked())
        return false;
    return (this->occupiedUnits.size() == 0);
}

bool Rock::isBlocked() {
    return this->building == nullptr;
}

Building* Rock::getBuilding() {
    return this->building;
}

int Rock::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord) || this->isBlocked())
        return 0;
    return unit.getSpeedWeightForSand();
}
Rock::~Rock() {}



Spice::Spice(u_int16_t quantity): Terrain(), quantity(quantity) {} 
int Spice::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedWeightForSand();
}
Spice::~Spice() {}



Dune::Dune(): Terrain() {}
int Dune::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedWeightForDune();
}
Dune::~Dune() {}


Mount::Mount(): Terrain() {}
int Mount::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedWeightForMount();
}
Mount::~Mount() {}

Cliff::Cliff(): Terrain() {}
int Cliff::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
        return 0;
    return unit.getSpeedWeightForCliff();
}

bool Cliff::isBlocked() {
    return true;
}

Cliff::~Cliff() {}
