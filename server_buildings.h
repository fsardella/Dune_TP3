#ifndef __SERVER_BUILDINGS_H__
#define __SERVER_BUILDINGS_H__

#include <stdint.h>
#include <utility>
#include "server_terrain_map.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

class Building {
    coor_t position;
    coor_t size;
    uint16_t actualLife;
    uint16_t totalLife;
 public:
    Building(coor_t position, coor_t size,
             uint16_t actualLife, uint16_t totalLife);
    coor_t getPosition();
    coor_t getSize();
    void build(TerrainMap& terr, uint16_t id);
    uint16_t getActualLife();
    uint16_t getTotalLife();
    void attack(uint16_t damage);
    bool destroyed();
    ~Building();
};


class Base: public Building {
 public:
    Base(coor_t position);
    ~Base();
};

#endif
