#ifndef __SERVER_WEAPONS_H__
#define __SERVER_WEAPONS_H__

#include <stdint.h>
#include <list>
#include "server_buildings.h"
class Unit;
class Building;

#define CHUNKSIZE 8

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
    uint16_t getType();
    void update();
    bool attack(Unit* objective);
    bool attack(Building* objective);
    Unit* scout(Unit* self);
    void startAttack();
    void stopAttack();
    bool isInRange(Unit* self, Unit* objective);
    bool isInRange(Unit* self, Building* objective);
    virtual ~Weapon();
};

class AssaultRifle: public Weapon {
 public:
    AssaultRifle(TerrainMap& terr, uint16_t range);
    virtual ~AssaultRifle();
};

#include "server_units.h"

#endif
