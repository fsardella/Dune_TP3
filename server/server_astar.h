#ifndef _ASTAR_H
#define _ASTAR_H

#include <stdint.h>
#include <vector>
#include <list>
#include <utility>
#include <map>



typedef std::pair<uint16_t, uint16_t> coor_t;

class Unit;
class TerrainMap;

//#include "server_units.h"
//#include "server_terrain_map.h"

class AStar {
    Unit& unit;
    std::list<coor_t> movs;
    std::list<coor_t> chunks;
    TerrainMap& terr;
    coor_t actPos;
    coor_t actDest;

    bool pathIsClear();
    std::list<coor_t> getAdjacents(const coor_t& coor);
    std::list<coor_t> getSubAdjacents(const coor_t& coor);
    void execAlgorithm();
    std::map<coor_t, coor_t> _execAlgorithm();
    float chevychev(const coor_t& coord);
    void execSubAlgorithm();
    std::map<coor_t, coor_t> _execSubAlgorithm(const coor_t& dest);
    
 public:
    AStar(Unit& unit, coor_t origin, TerrainMap& terrain);
    void processMove(coor_t dest);
    coor_t getPosition();
    void print();
};


#endif

