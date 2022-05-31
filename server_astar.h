#ifndef _ASTAR_H
#define _ASTAR_H

#include <stdint.h>
#include <vector>
#include <list>
#include <utility>
#include <map>


#include "server_units.h"
#include "server_terrain_map.h"


typedef std::pair<uint16_t, uint16_t> coor_t;

class Unit;
class TerrainMap;

class AStar {
    Unit& unit;
    std::list<coor_t> movs;
    TerrainMap& terr;
    coor_t actPos;
    coor_t actDest;

    bool path_is_clear();
    std::list<coor_t> getAdjacents(const coor_t& coor);
    void execAlgorithm();
    std::map<coor_t, coor_t> _execAlgorithm();
    float chevychev(const coor_t& coord);
    
 public:
    AStar(Unit& unit, coor_t origin, TerrainMap& terrain);
    void processMove(coor_t dest);
    coor_t getPosition();
};


#endif

