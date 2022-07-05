#ifndef __SERVER_WEAPONS_H__
#define __SERVER_WEAPONS_H__

#include <stdint.h>
#include <list>
#include "server_config.h"
#include "server_terrain_map.h"

class Unit;
class Building;

#define CHUNKSIZE 8

enum weaponTypes {
    ASSAULT_RIFLE = 0,
    CANNON,
    ROCKET_LAUNCHER,
    SOUND_WAVES,
    TTCANNON,
    PLASMA
};

class Weapon {
    uint16_t rechargeTime;
    uint16_t cooldown;
    uint16_t baseDamage;
    uint16_t type;
    uint16_t range;
    TerrainMap& terr;
    uint8_t shotsFired = 0;
    bool attacking = false;


    uint16_t manhattanDistance(coor_t dest, coor_t other);
    uint16_t getDamageModifier(Unit* objective);
    uint16_t getDamageModifier(Building* objective);
    uint16_t calculateDamage(Unit* objective);
    uint16_t calculateDamage(Building* objective);
 public:
    Weapon(uint16_t damage, uint16_t rechargeTime, uint16_t type,
           TerrainMap& terr, uint16_t range);
    uint16_t getType();
    void update();
    bool attack(Unit* objective);
    bool attack(Building* objective);
    Unit* scout(Unit* self);
    void startAttack();
    void stopAttack();
    virtual uint16_t getDamageModForVehicle();
    virtual uint16_t getDamageModForInfantry();
    virtual uint16_t getDamageModForBuilding();
    bool isInRange(Unit* self, Unit* objective);
    bool isInRange(Unit* self, Building* objective);
    virtual ~Weapon();
};

class AssaultRifle: public Weapon {
    uint16_t bonus;
 public:
    AssaultRifle(TerrainMap& ter, uint16_t range, Config* c);
    uint16_t getDamageModForInfantry();
    virtual ~AssaultRifle();
};

class Cannon: public Weapon {
 public:
    Cannon(TerrainMap& ter, uint16_t range, Config* c);
    virtual ~Cannon();
};

class RocketLauncher: public Weapon {
 public:
    RocketLauncher(TerrainMap& ter, uint16_t range, Config* c);
    virtual ~RocketLauncher();
};

class SoundWaves: public Weapon {
    uint16_t bonus;
 public:
    SoundWaves(TerrainMap& ter, uint16_t range, Config* c);
    uint16_t getDamageModForInfantry();
    virtual ~SoundWaves();
};

class TTCannon: public Weapon {
    uint16_t bonus;
 public:
    TTCannon(TerrainMap& ter, uint16_t range, Config* c);
    uint16_t getDamageModForVehicle();
    uint16_t getDamageModForBuilding();
    virtual ~TTCannon();
};

class PlasmaCannon: public Weapon {
    uint16_t bonus;
 public:
    PlasmaCannon(TerrainMap& ter, uint16_t range, Config* c);
    uint16_t getDamageModForVehicle();
    uint16_t getDamageModForBuilding();
    virtual ~PlasmaCannon();
};

#include "server_units.h"
#include "server_buildings.h"

#endif
