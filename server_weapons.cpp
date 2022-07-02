#include "server_weapons.h"


Weapon::Weapon(uint16_t damage, uint16_t rechargeTime, uint16_t type,
               TerrainMap& terr, uint16_t range):
               rechargeTime(rechargeTime), cooldown(rechargeTime),
               baseDamage(damage), type(type),
               range(range), terr(terr) {}

uint16_t Weapon::getType() {
    return this->type;
}

#define MODIFIER 0

uint16_t Weapon::calculateDamage(Unit* objective) {
    uint16_t totalDamage = 0;
    for (; this->shotsFired > 0; this->shotsFired--)
        totalDamage += this->baseDamage + MODIFIER;
    return totalDamage;
}

uint16_t Weapon::calculateDamage(Building* objective) {
    uint16_t totalDamage = 0;
    for (; this->shotsFired > 0; this->shotsFired--)
        totalDamage += this->baseDamage + MODIFIER;
    return totalDamage;
}

void Weapon::update() {
    if (this->attacking) {
        this->shotsFired = (this->cooldown + 30) / this->rechargeTime;
        this->cooldown = (this->cooldown + 30) % this->rechargeTime;
    } else {
        if (this->cooldown + 30 > this->rechargeTime)
            this->cooldown = this->rechargeTime;
        else
            this->cooldown += 30;
    }
}

uint16_t Weapon::manhattanDistance(coor_t dest, coor_t other) {
    return (uint16_t)(abs((int)dest.first - (int)other.first)
                    + abs((int)other.second - (int)other.second)) / CHUNKSIZE;
}

bool Weapon::isInRange(Unit* self, Unit* objective) {
    return (this->manhattanDistance(self->getPosition(), objective->getPosition())
           <= this->range);
}

bool Weapon::isInRange(Unit* self, Building* objective) {
    uint16_t selfX = self->getPosition().second;
    uint16_t selfY = self->getPosition().first;
    for (uint16_t i = selfY - this->range * CHUNKSIZE;
         i <= selfY + this->range * CHUNKSIZE;
         i += CHUNKSIZE) {
        for (uint16_t j = selfX - this->range * CHUNKSIZE;
             j <= selfX + this->range * CHUNKSIZE;
             j += CHUNKSIZE) {
            coor_t act = coor_t(i, j);
            if (this->manhattanDistance(act, coor_t(selfY, selfX)) > this->range)
                continue;
            if (this->terr.getBuilding(act) == nullptr ||
                this->terr.getBuilding(act)->getID() != objective->getID())
                continue;
            return true;
        }
    }
    return false;
}

Unit* Weapon::scout(Unit* self) {
    uint16_t selfX = self->getPosition().second;
    uint16_t selfY = self->getPosition().first;
    for (uint16_t i = selfY - this->range * CHUNKSIZE;
         i <= selfY + this->range * CHUNKSIZE;
         i += CHUNKSIZE) {
        for (uint16_t j = selfX - this->range * CHUNKSIZE;
             j <= selfX + this->range * CHUNKSIZE;
             j += CHUNKSIZE) {
            coor_t act = coor_t(i, j);
            if (this->manhattanDistance(act, coor_t(selfY, selfX)) > this->range)
                continue;
            std::list<Unit*> unitsInChunk = this->terr.getAllUnits(act);
            for (Unit*& unit : unitsInChunk) {
                if (!unit->isDead() && unit->getOwner() != self->getOwner())
                    return unit;
            }
        }
    }
    return nullptr;
}


bool Weapon::attack(Unit* objective) {
    uint16_t actDamage = this->calculateDamage(objective);
    if (actDamage == 0)
        return false;
    objective->damage(actDamage);
    return true;
}

bool Weapon::attack(Building* objective) {
    uint16_t actDamage = this->calculateDamage(objective);
    if (actDamage == 0)
        return false;
    objective->attack(actDamage);
    return true;
}

void Weapon::startAttack() {
    this->attacking = true;
}

void Weapon::stopAttack() {
    this->attacking = false;
}



Weapon::~Weapon() {}


AssaultRifle::AssaultRifle(TerrainMap& ter, uint16_t range):
                                                Weapon(2, 50, 0, ter, range) {}



AssaultRifle::~AssaultRifle() {}
