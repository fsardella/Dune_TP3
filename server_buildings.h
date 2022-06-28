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
    uint16_t buildingID = 0xFFFF;
    uint16_t watchers = 0;
 public:
    Building(coor_t position, coor_t size, uint16_t totalLife);
    coor_t getPosition();
    coor_t getSize();
    virtual bool isLightFactory();
    bool canBuild(TerrainMap& terr);
    uint16_t getID();
    void build(TerrainMap& terr, uint16_t id);
    uint16_t getActualLife();
    uint16_t getTotalLife();
    void attack(uint16_t damage);
    bool destroyed();
    void watch();
    void stopWatching();
    bool canBeCleaned();
    virtual ~Building();
};


class Base: public Building {
 public:
    Base(coor_t position);
    virtual ~Base();
};

class LightFactory : public Building {
 public:
    LightFactory(coor_t position);
    bool isLightFactory();
    virtual ~LightFactory();
};

#endif
