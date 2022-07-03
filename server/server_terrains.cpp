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

uint16_t Terrain::harvestMenage(uint16_t freeSpace) {
    return 0;
}

uint16_t Terrain::peekMenage() {
    return 0;
}

bool Terrain::isThereARefinery() {
     return false;
}

bool Terrain::hasMenage() {
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

float Terrain::getSpeedMod() {
    return 1;
}

bool Terrain::isBlocked() {
    return false;
}

bool Terrain::isOccupied(coor_t coord) {
    return (this->occupiedUnits.find(coord) != this->occupiedUnits.end());
}


Sand::Sand(): Terrain() {}
int Sand::getSpeedWeight(Unit& unit, coor_t coord) {
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
    return this->building != nullptr;
}

void Rock::eraseBuilding() {
    this->building = nullptr;    
}

Building* Rock::getBuilding() {
    return this->building;
}

bool Rock::isThereARefinery() {
    if (this->building == nullptr)
        return false;
    return this->building->isRefinery();
}

int Rock::getSpeedWeight(Unit& unit, coor_t coord) {
    if (this->isBlocked())
        return 0;
    return unit.getSpeedWeightForSand();
}
Rock::~Rock() {}



Spice::Spice(u_int16_t quantity): Terrain(), quantity(quantity) {} 
int Spice::getSpeedWeight(Unit& unit, coor_t coord) {
    return unit.getSpeedWeightForSand();
}

uint16_t Spice::harvestMenage(uint16_t freeSpace) {
    uint16_t ret;
    if (this->quantity < freeSpace) {
        ret = this->quantity;
        this->quantity = 0;
    } else {
        ret = freeSpace;
        this->quantity -= freeSpace;
    }
    return ret;
}

uint16_t Spice::peekMenage() {
    return this->quantity;
}

bool Spice::hasMenage() {
    return (this->quantity != 0);
}

Spice::~Spice() {}



Dune::Dune(): Terrain() {}
int Dune::getSpeedWeight(Unit& unit, coor_t coord) {
    return unit.getSpeedWeightForDune();
}

float Dune::getSpeedMod() {
    return 0.5;
}

Dune::~Dune() {}


Mount::Mount(): Terrain() {}
int Mount::getSpeedWeight(Unit& unit, coor_t coord) {
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
