#ifndef _SERVER_TERRAIN_MAP_H
#define _SERVER_TERRAIN_MAP_H

#include <list>
#include <vector>

#include <stdint.h>


typedef std::pair<uint16_t, uint16_t> coor_t;
typedef std::vector<std::vector<int>> sketch_t;

class Terrain;

#include "server_terrains.h"
#include "server_units.h"

class TerrainMap {
    std::vector<std::vector<Terrain*>> terr;

 public:
    TerrainMap();
    TerrainMap(sketch_t mapSketch);
    void print(coor_t org, coor_t dest); // debug
    void printDebug();
    coor_t getDims();
    bool isInsideMap(coor_t place);
    bool isOccupied(coor_t coord);
    bool isBlocked(coor_t coord);
    bool canBuild(coor_t coor, coor_t size);
    void build(coor_t coor, coor_t size, uint16_t id);
    void swapContent(coor_t source, coor_t destiny);
    int getSpeedWeight(coor_t coor, Unit& unit);
    ~TerrainMap();
    
    TerrainMap(const TerrainMap&) = delete;
    TerrainMap& operator=(const TerrainMap&) = delete;

    TerrainMap(TerrainMap&&);
    TerrainMap& operator=(TerrainMap&&);
};

#endif


