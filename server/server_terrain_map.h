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
#include "server_buildings.h"
#include <list>

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
    void build(coor_t coor, Building* building);
    bool hasMenage(coor_t coor);
    uint16_t harvestMenage(coor_t coor, uint16_t freeSpace);
    bool isThereARefinery(coor_t coor);
    void eraseBuildingFromMap(coor_t coor, coor_t size);
    void eraseUnitFromMap(coor_t coor);
    Building* getBuilding(coor_t coor);
    Unit* getUnit(coor_t coor);
    std::list<Unit*> getAllUnits(coor_t coor);
    void swapContent(coor_t source, coor_t destiny);
    int getSpeedWeight(coor_t coor, Unit& unit);
    float getSpeedMod(coor_t coor);
    void addMenageData(std::list<std::pair<coor_t, uint16_t>>& data);
    ~TerrainMap();
    
    TerrainMap(const TerrainMap&) = delete;
    TerrainMap& operator=(const TerrainMap&) = delete;

    TerrainMap(TerrainMap&&);
    TerrainMap& operator=(TerrainMap&&);
};

#endif


