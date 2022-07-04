#ifndef __SERVER_BUILDINGS_H__
#define __SERVER_BUILDINGS_H__

#include <stdint.h>
#include <utility>
#include <string>
#include "server_terrain_map.h"
#include "common_command.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

#ifndef BUILDINGTYPES
#define BUILDINGTYPES
enum buildingTypes {
    BASE = 11,
    LIGHT_FACTORY,
    HEAVY_FACTORY,
    PALACE,
    REFINERY,
    SILO,
    WINDTRAP,
    BARRACK
};
#endif

class Building {
    coor_t size;
    uint16_t actualLife;
    uint16_t totalLife;
    uint16_t buildingID = 0xFFFF;
    uint16_t buildingTime;
    uint16_t actualTime = 0;
    int watchers = 0;
    TerrainMap* terrain;
    std::string owner;
    
    void eraseFromMap();
 protected:
    coor_t position = coor_t(0xFFFF, 0xFFFF);
 public:
    Building(coor_t size, uint16_t totalLife, uint16_t buildingTime,
             std::string owner);
    static Building* newBuilding(uint8_t type, std::string owner);

    coor_t getPosition();
    coor_t getSize();
    virtual uint32_t getMoneyCapacity();
    virtual uint32_t gatherMoney(uint32_t actualMoney, uint32_t moneyCapacity);
    virtual void rechargeMoney(uint32_t menage) {}
    virtual bool isLightFactory();
    virtual bool isHeavyFactory();
    virtual bool isRefinery();
    
    void update(uint16_t constructionTime);
    uint8_t getCompletion();
    
    bool canBuild(TerrainMap& terr, coor_t position);
    uint16_t getID();
    std::string getOwner();
    virtual uint16_t getType() = 0;
    void build(TerrainMap& terr, coor_t position, uint16_t id);
    uint16_t getActualLife();
    uint16_t getTotalLife();
    void attack(uint16_t damage);
    void destroy(std::list<Command>& events);
    bool destroyed();

    void watch();
    void stopWatching();
    bool canBeCleaned();

    virtual int32_t getEnergy();
    virtual ~Building();
};


class Base: public Building {
 public:
    Base(coor_t position, std::string owner);
    uint16_t getType();
    virtual ~Base();
};

class LightFactory : public Building {
 public:
    LightFactory(std::string owner);
    bool isLightFactory() override;
    int32_t getEnergy();
    uint16_t getType();
    virtual ~LightFactory();
};

class HeavyFactory : public Building {
 public:
    HeavyFactory(std::string owner);
    bool isHeavyFactory();
    int32_t getEnergy();
    uint16_t getType();
    virtual ~HeavyFactory();
};

class Refinery : public Building {
    uint32_t money = 0;
 public:
    Refinery(std::string owner);
    bool isRefinery();
    uint32_t gatherMoney(uint32_t actualMoney, uint32_t moneyCapacity);
    uint32_t getMoneyCapacity();
    void rechargeMoney(uint32_t menage);
    int32_t getEnergy();
    uint16_t getType();
    virtual ~Refinery();
};

class WindTrap : public Building {
 public:
    WindTrap(std::string owner);
    int32_t getEnergy();
    uint16_t getType();
    virtual ~WindTrap();
};

#endif
