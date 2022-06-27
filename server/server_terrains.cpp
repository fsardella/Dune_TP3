#include "server_terrains.h"

#include <iostream>

Terrain::Terrain() {}
Terrain::~Terrain() {}

void Terrain::occupySpace(coor_t coord) {
    this->occupied.insert(coord);
}
void Terrain::freeSpace(coor_t coord) {
    this->occupied.erase(coord);
}

void Terrain::printDebug() {
    for (coor_t tile : this->occupied) {
        std::cout << tile.first << ", " << tile.second << "; ";
    }
}

bool Terrain::isOccupied(coor_t coord) {
    return (this->occupied.find(coord) != this->occupied.end());
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
void Rock::build(char building) {
    this->Building = building;
    //this->occupySpace(); // TODO
}
int Rock::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
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
Cliff::~Cliff() {}