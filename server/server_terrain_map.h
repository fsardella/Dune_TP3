#ifndef _SERVER_TERRAIN_MAP_H
#define _SERVER_TERRAIN_MAP_H

#include <list>
#include <vector>

#include <stdint.h>

#include "server_terrains.h"
#include "server_units.h"

typedef std::pair<uint16_t, uint16_t> coor_t;
typedef std::vector<std::vector<int>> sketch_t;

class TerrainMap {
    std::vector<std::vector<Terrain*>> terr;

 public:
    TerrainMap(sketch_t mapSketch);
    void print(coor_t org, coor_t dest); // debug
    coor_t getDims();
    void swapContent(coor_t source, coor_t destiny);
    int getSpeed(coor_t coor, Unit& unit);
    ~TerrainMap();
};

#endif


