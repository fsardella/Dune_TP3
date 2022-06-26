#include "server_terrain_map.h"

#include <iostream>

#include "server_units.h"

enum sketchElements {
<<<<<<< HEAD
    SAND = 0,
    DUNE,
    ROCK,
    MOUNT,
    CLIFF,
=======
    CLIFF = 0,
    SAND,
    DUNE,
    MOUNT,
    ROCK,
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    SPICE,
    BUILDING,
};

<<<<<<< HEAD
TerrainMap::TerrainMap(sketch_t mapSketch) {
    for (std::vector<int> row : mapSketch) {
        for (int elem : row) {
            std::vector<Terrain*> row_res;
=======
#define CHUNKSIZE 8

TerrainMap::TerrainMap() {}

TerrainMap::TerrainMap(sketch_t mapSketch) {
    for (std::vector<int> row : mapSketch) {
        std::vector<Terrain*> row_res;
        for (int elem : row) {
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
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
                case BUILDING:
                    Rock* terr = new Rock();
                    terr->build('b');
                    row_res.push_back(terr);
                    break;
            }
<<<<<<< HEAD
            this->terr.push_back(row_res);
        }
=======
        }
        this->terr.push_back(row_res);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    }
}


void TerrainMap::print(coor_t org, coor_t dest) {
    coor_t dims = this->getDims();
<<<<<<< HEAD
    for (size_t i = 0; i < dims.first; i++) {
        std::cout << i;
        for (size_t j = 0; j < dims.second; j++) {
            Terrain* draw = this->terr[i][j];
            if (org.first == i && org.second == j)
                std::cout << '@';
            else if (dest.first == i && dest.second == j)
=======
    for (size_t i = 0; i < dims.first / CHUNKSIZE; i++) {
        for (size_t j = 0; j < dims.second / CHUNKSIZE; j++) {
            Terrain* draw = this->terr[i][j];
            if (org.first / CHUNKSIZE == i && org.second / CHUNKSIZE == j)
                std::cout << '@';
            else if (dest.first / CHUNKSIZE == i && dest.second / CHUNKSIZE == j)
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
                std::cout << 'X';
            else
                draw->print();
        }
<<<<<<< HEAD
        std::cout << std::endl;
    }
}

=======
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

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
coor_t TerrainMap::getDims() {
    if (this->terr.size() == 0)
        return coor_t(0, 0);
    // Terrain siempre sera una matriz
<<<<<<< HEAD
    return coor_t(this->terr.size(), this->terr[0].size());
}

void TerrainMap::swapContent(coor_t source, coor_t destiny) {
    this->terr[source.first][source.second]->freeSpace();
    this->terr[destiny.first][destiny.second]->occupySpace();
=======
    return coor_t(this->terr.size() * CHUNKSIZE, this->terr[0].size() * CHUNKSIZE);
}


void TerrainMap::swapContent(coor_t source, coor_t destiny) {
    this->terr[source.first / CHUNKSIZE][source.second / CHUNKSIZE]->freeSpace(source);
    this->terr[destiny.first / CHUNKSIZE][destiny.second / CHUNKSIZE]->occupySpace(destiny);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
}


int TerrainMap::getSpeed(coor_t coor, Unit& unit) {
<<<<<<< HEAD
    return this->terr[coor.first][coor.second]->getSpeed(unit);
=======
    return this->terr[coor.first / CHUNKSIZE][coor.second / CHUNKSIZE]->getSpeed(unit, coor);
}

bool TerrainMap::isOccupied(coor_t coord) {
    return this->terr[coord.first / CHUNKSIZE][coord.second / CHUNKSIZE]->isOccupied(coord);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
}

TerrainMap::~TerrainMap() {
    for (std::vector<Terrain*> row : this->terr) {
        for (Terrain* elem : row) {
            delete elem;    
        }
    }
}

<<<<<<< HEAD
=======
TerrainMap::TerrainMap(TerrainMap&& other) : terr(std::move(other.terr)) {}

TerrainMap& TerrainMap::operator=(TerrainMap&& other) {
    if (this == &other)
        return *this;
    this->terr = std::move(other.terr);
    return *this;
}

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
