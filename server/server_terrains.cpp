#include "server_terrains.h"

#include <iostream>

<<<<<<< HEAD
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
=======
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
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
        return 0;
    return unit.getSpeedForSand();
}
Sand::~Sand() {}

//debug
<<<<<<< HEAD
void Terrain::print() {}

void Sand::print() {
=======
void Terrain::print() {
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
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
<<<<<<< HEAD
    this->occupySpace();
}
int Rock::getSpeed(Unit& unit) {
    if (this->occupied)
=======
    //this->occupySpace(); // TODO
}
int Rock::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
        return 0;
    return unit.getSpeedForSand();
}
Rock::~Rock() {}



Spice::Spice(u_int16_t quantity): Terrain(), quantity(quantity) {} 
<<<<<<< HEAD
int Spice::getSpeed(Unit& unit) {
    if (this->occupied)
=======
int Spice::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
        return 0;
    return unit.getSpeedForSand();
}
Spice::~Spice() {}



Dune::Dune(): Terrain() {}
<<<<<<< HEAD
int Dune::getSpeed(Unit& unit) {
    if (this->occupied)
=======
int Dune::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
        return 0;
    return unit.getSpeedForDune();
}
Dune::~Dune() {}


Mount::Mount(): Terrain() {}
<<<<<<< HEAD
int Mount::getSpeed(Unit& unit) {
    if (this->occupied)
=======
int Mount::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
        return 0;
    return unit.getSpeedForMount();
}
Mount::~Mount() {}

Cliff::Cliff(): Terrain() {}
<<<<<<< HEAD
int Cliff::getSpeed(Unit& unit) {
    if (this->occupied)
=======
int Cliff::getSpeed(Unit& unit, coor_t coord) {
    if (this->isOccupied(coord))
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
        return 0;
    return unit.getSpeedForCliff();
}
Cliff::~Cliff() {}
