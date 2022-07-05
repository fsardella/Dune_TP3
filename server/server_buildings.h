#ifndef __SERVER_BUILDINGS_H__
#define __SERVER_BUILDINGS_H__

#include <stdint.h>
#include <utility>
#include <string>
#include "server_terrain_map.h"
#include "common_command.h"
#include "server_config.h"
#include "server_weapons.h"

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

class Weapon;

class Building {
    coor_t size;
    uint16_t actualLife;
    uint16_t totalLife;
    uint16_t buildingID = 0xFFFF;
    uint16_t buildingTime;
    uint16_t actualTime = 0;
    int32_t energy;
    int watchers = 0;
    std::string owner;
    TerrainMap* terrain;
    
    void eraseFromMap();
 protected:
    coor_t position = coor_t(0xFFFF, 0xFFFF);
 public:
    Building(coor_t size, uint16_t totalLife, uint16_t buildingTime,
             int32_t energy, std::string owner);
    static Building* newBuilding(uint8_t type, std::string owner, Config* c);

    coor_t getPosition();
    coor_t getSize();
    virtual uint32_t getMoneyCapacity();
    virtual uint32_t gatherMoney(uint32_t actualMoney, uint32_t moneyCapacity);
    virtual void rechargeMoney(uint32_t menage) {}
    virtual bool isLightFactory();
    virtual bool isHeavyFactory();
    virtual bool isRefinery();
    virtual bool isPalace();
    virtual bool isBarrack();
    
    void update(uint16_t constructionTime);
    uint8_t getCompletion();
    
    uint16_t getDamageFor(Weapon* weapon);
    
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

    int32_t getEnergy();
    virtual ~Building();
};


class Base: public Building {
 public:
    Base(coor_t position, std::string owner, Config* c);
    Base(); // TE ODIO STD:: POR QUE NECESITAS PORQUERIAS VACIAS
    uint16_t getType() override;
    virtual ~Base();
};

class LightFactory : public Building {
 public:
    LightFactory(std::string owner, Config* c);
    bool isLightFactory() override;
    uint16_t getType() override;
    virtual ~LightFactory();
};

class HeavyFactory : public Building {
 public:
    HeavyFactory(std::string owner, Config* c);
    bool isHeavyFactory() override;
    int32_t getEnergy();
    uint16_t getType() override;
    virtual ~HeavyFactory();
};

class Palace : public Building {
 public:
    Palace(std::string owner, Config* c);
    bool isPalace() override;
    uint16_t getType() override;
    virtual ~Palace();
};

class Refinery : public Building {
    uint32_t moneyCap;
    uint32_t money = 0;
 public:
    Refinery(std::string owner, Config* c);
    bool isRefinery() override;
    uint32_t gatherMoney(uint32_t actualMoney, uint32_t moneyCapacity)
            override;
    uint32_t getMoneyCapacity() override;
    void rechargeMoney(uint32_t menage) override;
    uint16_t getType() override;
    virtual ~Refinery();
};

class Silo : public Building {
    uint32_t moneyCap;
 public:
    Silo(std::string owner, Config* c);
    uint32_t getMoneyCapacity() override;
    uint16_t getType() override;
    virtual ~Silo();
};

class WindTrap : public Building {
 public:
    WindTrap(std::string owner, Config* c);
    uint16_t getType() override;
    virtual ~WindTrap();
};

class Barrack : public Building {
  public:
    Barrack(std::string owner, Config* c);
    bool isBarrack() override;
    uint16_t getType() override;
    virtual ~Barrack();
};

#endif
