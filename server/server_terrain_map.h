#ifndef _SERVER_TERRAIN_MAP_H
#define _SERVER_TERRAIN_MAP_H

#include <list>
#include <vector>

#include <stdint.h>

<<<<<<< HEAD
#include "server_terrains.h"
#include "server_units.h"
=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd

typedef std::pair<uint16_t, uint16_t> coor_t;
typedef std::vector<std::vector<int>> sketch_t;

<<<<<<< HEAD
=======
class Terrain;

#include "server_terrains.h"
#include "server_units.h"

>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
class TerrainMap {
    std::vector<std::vector<Terrain*>> terr;

 public:
<<<<<<< HEAD
    TerrainMap(sketch_t mapSketch);
    void print(coor_t org, coor_t dest); // debug
    coor_t getDims();
    void swapContent(coor_t source, coor_t destiny);
    int getSpeed(coor_t coor, Unit& unit);
    ~TerrainMap();
=======
    TerrainMap();
    TerrainMap(sketch_t mapSketch);
    void print(coor_t org, coor_t dest); // debug
    void printDebug();
    coor_t getDims();
    bool isOccupied(coor_t coord);
    void swapContent(coor_t source, coor_t destiny);
    int getSpeed(coor_t coor, Unit& unit);
    ~TerrainMap();
    
    TerrainMap(const TerrainMap&) = delete;
    TerrainMap& operator=(const TerrainMap&) = delete;

    TerrainMap(TerrainMap&&);
    TerrainMap& operator=(TerrainMap&&);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
};

#endif


