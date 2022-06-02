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
    BUILDING,
};

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
                case BUILDING:
                    Rock* terr = new Rock();
                    terr->build('b');
                    row_res.push_back(terr);
                    break;
            }
        }
        this->terr.push_back(row_res);
    }
}


void TerrainMap::print(coor_t org, coor_t dest) {
    coor_t dims = this->getDims();
    for (size_t i = 0; i < dims.first; i++) {
        std::cout << i;
        for (size_t j = 0; j < dims.second; j++) {
            Terrain* draw = this->terr[i][j];
            if (org.first == i && org.second == j)
                std::cout << '@';
            else if (dest.first == i && dest.second == j)
                std::cout << 'X';
            else
                draw->print();
        }
        std::cout << std::endl;
    }
}

coor_t TerrainMap::getDims() {
    if (this->terr.size() == 0)
        return coor_t(0, 0);
    // Terrain siempre sera una matriz
    return coor_t(this->terr.size(), this->terr[0].size());
}

void TerrainMap::swapContent(coor_t source, coor_t destiny) {
    this->terr[source.first][source.second]->freeSpace();
    this->terr[destiny.first][destiny.second]->occupySpace();
}


int TerrainMap::getSpeed(coor_t coor, Unit& unit) {
    return this->terr[coor.first][coor.second]->getSpeed(unit);
}

TerrainMap::~TerrainMap() {
    for (std::vector<Terrain*> row : this->terr) {
        for (Terrain* elem : row) {
            delete elem;    
        }
    }
}

