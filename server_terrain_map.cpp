#include "server_terrain_map.h"

#include <iostream>

#include "server_units.h"

enum sketchElements {
    CLIFF = 0,
    SAND,
    DUNE,
    MOUNT,
    ROCK,
    SPICE,
};

#define CHUNKSIZE 8

TerrainMap::TerrainMap() {}

TerrainMap::TerrainMap(sketch_t mapSketch) {
    for (std::vector<int> row : mapSketch) {
        std::vector<Terrain*> row_res;
        for (int elem : row) {
            // Usar case es mas facil, esto solo se ejecuta una vez en todo el
            // programa, asi que no me preocupa la velocidad
            switch (elem) {
                case SAND:
                    row_res.push_back(new Sand());
                    break;
                case DUNE:
                    row_res.push_back(new Dune());
                    break;
                case ROCK:
                    row_res.push_back(new Rock());
                    break;
                case MOUNT:
                    row_res.push_back(new Mount());
                    break;
                case CLIFF:
                    row_res.push_back(new Cliff());
                    break;
                case SPICE:
                    row_res.push_back(new Spice(69));
                    break;
            }
        }
        this->terr.push_back(row_res);
    }
}

void TerrainMap::print(coor_t org, coor_t dest) {
    coor_t dims = this->getDims();
    for (size_t i = 0; i < dims.first / CHUNKSIZE; i++) {
        for (size_t j = 0; j < dims.second / CHUNKSIZE; j++) {
            Terrain* draw = this->terr[i][j];
            if (org.first / CHUNKSIZE == i && org.second / CHUNKSIZE == j)
                std::cout << '@';
            else if (dest.first / CHUNKSIZE == i && dest.second / CHUNKSIZE == j)
                std::cout << 'X';
            else
                draw->print();
        }
        std::cout << i * CHUNKSIZE << std::endl;
    }
}

void TerrainMap::printDebug() {
    std::cout << "Occupied coordinates: ";
    for (std::vector<Terrain*> row : this->terr) {
        for (Terrain* terry : row) {
            terry->printDebug();
        }
    }
    std::cout << std::endl;
}

coor_t TerrainMap::getDims() {
    if (this->terr.size() == 0)
        return coor_t(0, 0);
    // Terrain siempre sera una matriz
    return coor_t(this->terr.size() * CHUNKSIZE, this->terr[0].size() * CHUNKSIZE);
}


bool TerrainMap::isInsideMap(coor_t place) {
    coor_t dims = this->getDims();
    return (place.first < dims.first && place.second < dims.second); 
}

void TerrainMap::swapContent(coor_t source, coor_t destiny) {
    if (!this->isInsideMap(source) || !this->isInsideMap(destiny))
        return;
    uint16_t id = this->terr[source.first / CHUNKSIZE][source.second / CHUNKSIZE]->getIdOfOccupant(source);
    this->terr[source.first / CHUNKSIZE][source.second / CHUNKSIZE]->freeSpace(source);
    this->terr[destiny.first / CHUNKSIZE][destiny.second / CHUNKSIZE]->occupySpace(destiny, id);
}


int TerrainMap::getSpeedWeight(coor_t coor, Unit& unit) {
    if (!this->isInsideMap(coor))
        return 0;
    return this->terr[coor.first / CHUNKSIZE][coor.second / CHUNKSIZE]->getSpeedWeight(unit, coor);
}

bool TerrainMap::canBuild(coor_t coor, coor_t size) {
    for (uint16_t i = 0; i < size.first; i++) {
        for (uint16_t j = 0; j < size.second; j++) {
            if (!this->isInsideMap(coor_t(i,j)))
                return false;
            if (!this->terr[coor.first / CHUNKSIZE + i][coor.second / CHUNKSIZE + j]->canBuild())
                return false;
        }
    }
    return true;
}

void TerrainMap::build(coor_t coor, coor_t size, uint16_t id) {
    for (uint16_t i = 0; i < size.first; i++) {
        for (uint16_t j = 0; j < size.second; j++) {
            this->terr[coor.first / CHUNKSIZE + i][coor.second / CHUNKSIZE + j]->build(*this, id);
        }
    }   
}

bool TerrainMap::isOccupied(coor_t coord) {
    if (!this->isInsideMap(coord))
        return true;
    return this->terr[coord.first / CHUNKSIZE][coord.second / CHUNKSIZE]->isOccupied(coord);
}

bool TerrainMap::isBlocked(coor_t coord) {
    if (!this->isInsideMap(coord))
        return true;
    return this->terr[coord.first / CHUNKSIZE][coord.second / CHUNKSIZE]->isBlocked();
}

TerrainMap::~TerrainMap() {
    for (std::vector<Terrain*> row : this->terr) {
        for (Terrain* elem : row) {
            delete elem;    
        }
    }
}

TerrainMap::TerrainMap(TerrainMap&& other) : terr(std::move(other.terr)) {}

TerrainMap& TerrainMap::operator=(TerrainMap&& other) {
    if (this == &other)
        return *this;
    this->terr = std::move(other.terr);
    return *this;
}
