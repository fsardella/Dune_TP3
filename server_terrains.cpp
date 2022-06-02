#include "server_terrains.h"

#include <iostream>

Terrain::Terrain(): occupied(false) {}
Terrain::~Terrain() {}

void Terrain::occupySpace() {
    this->occupied = true;
}
void Terrain::freeSpace() {
    this->occupied = false;
}



Sand::Sand(): Terrain() {}
int Sand::getSpeed(Unit& unit) {
    if (this->occupied)
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
    this->occupySpace();
}
int Rock::getSpeed(Unit& unit) {
    if (this->occupied)
        return 0;
    return unit.getSpeedForSand();
}
Rock::~Rock() {}



Spice::Spice(u_int16_t quantity): Terrain(), quantity(quantity) {} 
int Spice::getSpeed(Unit& unit) {
    if (this->occupied)
        return 0;
    return unit.getSpeedForSand();
}
Spice::~Spice() {}



Dune::Dune(): Terrain() {}
int Dune::getSpeed(Unit& unit) {
    if (this->occupied)
        return 0;
    return unit.getSpeedForDune();
}
Dune::~Dune() {}


Mount::Mount(): Terrain() {}
int Mount::getSpeed(Unit& unit) {
    if (this->occupied)
        return 0;
    return unit.getSpeedForMount();
}
Mount::~Mount() {}

Cliff::Cliff(): Terrain() {}
int Cliff::getSpeed(Unit& unit) {
    if (this->occupied)
        return 0;
    return unit.getSpeedForCliff();
}
Cliff::~Cliff() {}
