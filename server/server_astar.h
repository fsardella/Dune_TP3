#ifndef _ASTAR_H
#define _ASTAR_H

#include <stdint.h>
#include <vector>
#include <list>
#include <utility>
#include <map>


<<<<<<< HEAD
#include "server_units.h"
#include "server_terrain_map.h"

=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd

typedef std::pair<uint16_t, uint16_t> coor_t;

class Unit;
class TerrainMap;

<<<<<<< HEAD
class AStar {
    Unit& unit;
    std::list<coor_t> movs;
=======
//#include "server_units.h"
//#include "server_terrain_map.h"

class AStar {
    Unit& unit;
    std::list<coor_t> movs;
    std::list<coor_t> chunks;
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    TerrainMap& terr;
    coor_t actPos;
    coor_t actDest;

<<<<<<< HEAD
    bool path_is_clear();
    std::list<coor_t> getAdjacents(const coor_t& coor);
    void execAlgorithm();
    std::map<coor_t, coor_t> _execAlgorithm();
    float chevychev(const coor_t& coord);
=======
    bool pathIsClear();
    std::list<coor_t> getAdjacents(const coor_t& coor);
    std::list<coor_t> getSubAdjacents(const coor_t& coor);
    void execAlgorithm();
    std::map<coor_t, coor_t> _execAlgorithm();
    float chevychev(const coor_t& coord);
    void execSubAlgorithm();
    std::map<coor_t, coor_t> _execSubAlgorithm(const coor_t& dest);
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    
 public:
    AStar(Unit& unit, coor_t origin, TerrainMap& terrain);
    void processMove(coor_t dest);
    coor_t getPosition();
<<<<<<< HEAD
=======
    void print();
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
};


#endif

