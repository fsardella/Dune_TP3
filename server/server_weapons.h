#ifndef __SERVER_WEAPONS_H__
#define __SERVER_WEAPONS_H__

#include <stdint.h>
#include <list>
#include <utility>
#include <tuple>
#include "server_config.h"
#include "server_terrain_map.h"

class Unit;
class Building;

#define CHUNKSIZE 8

enum weaponTypes {
    ASSAULT_RIFLE = 0,
    ROCKET_LAUNCHER,
    TTCANNON,
    CANNON,
    SOUND_WAVES,
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
    uint16_t calculateDamage(Unit* objective);
    uint16_t calculateDamage(Building* objective);
 public:
    Weapon(uint16_t damage, uint16_t rechargeTime, uint16_t type,
           TerrainMap& terr, uint16_t range);
    virtual uint16_t getType();
    virtual void update();
    virtual bool attack(Unit* objective);
    virtual bool attack(Building* objective);
    Unit* scout(Unit* self);
    virtual void startAttack();
    virtual void stopAttack();
    uint16_t getDamageModifier(Unit* objective);
    uint16_t getDamageModifier(Building* objective);
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


class TwoHanded : public Weapon { // Solo hereda de weapon por los punteros
    std::pair<Weapon*, Weapon*> weapons;
    bool usedFirst = true;
 public:
    TwoHanded(TerrainMap& ter, uint16_t range, Config* c);
    uint16_t getType();
    void update();
    bool attack(Unit* objective);
    bool attack(Building* objective);
    void startAttack();
    void stopAttack();
    ~TwoHanded();
};

#include "server_units.h"
#include "server_buildings.h"

#endif
