#include "server_weapons.h"
#include <iostream>
#include <cmath>
#include <set>

#ifndef BROADCASTOPERS
#define BROADCASTOPERS
enum broadcastOpers {
    SUCCESS = 0,
    FAILURE,
    UNIT_BROADCAST,
    BUILDING_BUILT,
    UNIT_ATTACKED,
    BUILDING_ATTACKED,
    LOST_GAME,
    WON_GAME,
    UNIT_WIP,
    BUILDING_WIP,
    WORM,
    MENAGE
};
#endif



Weapon::Weapon(uint16_t damage, uint16_t rechargeTime, uint16_t type,
               TerrainMap& terr, uint16_t range):
               rechargeTime(rechargeTime), cooldown(rechargeTime),
               baseDamage(damage), type(type),
               range(range), terr(terr) {}

uint16_t Weapon::getType() {
    return this->type;
}

uint16_t Weapon::getDamageModifier(Unit* objective) {
    return objective->getDamageFor(this);
}


uint16_t Weapon::getDamageModifier(Building* objective) {
    return objective->getDamageFor(this);    
}


uint16_t Weapon::calculateDamage(Unit* objective) {
    uint16_t totalDamage = 0;
    for (; this->shotsFired > 0; this->shotsFired--)
        totalDamage += this->baseDamage + this->getDamageModifier(objective);
    return totalDamage;
}

uint16_t Weapon::calculateDamage(Building* objective) {
    uint16_t totalDamage = 0;
    for (; this->shotsFired > 0; this->shotsFired--)
        totalDamage += this->baseDamage + this->getDamageModifier(objective);
    return totalDamage;
}

uint16_t Weapon::getDamageModForVehicle() {
    return 0;
}
uint16_t Weapon::getDamageModForInfantry() {
    return 0;
}
uint16_t Weapon::getDamageModForBuilding() {
    return 0;
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
                    + abs((int)dest.second - (int)other.second)) / CHUNKSIZE;
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
            for (Unit* unit : unitsInChunk) {
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




AssaultRifle::AssaultRifle(TerrainMap& ter, uint16_t range, Config* c):
                                Weapon(c->ASSAULT_RIFLE_DAMAGE,
                                c->ASSAULT_RIFLE_COOLDOWN, ASSAULT_RIFLE,
                                ter, range),
                                bonus(c->ASSAULT_RIFLE_BONUS) {}

uint16_t AssaultRifle::getDamageModForInfantry() {
    return this->bonus;
}

AssaultRifle::~AssaultRifle() {}





Cannon::Cannon(TerrainMap& ter, uint16_t range, Config* c):
                                Weapon(c->CANNON_DAMAGE,
                                c->CANNON_COOLDOWN, CANNON,
                                ter, range) {}

Cannon::~Cannon() {}




RocketLauncher::RocketLauncher(TerrainMap& ter, uint16_t range, Config* c):
                                Weapon(c->ROCKET_LAUNCHER_DAMAGE,
                                c->ROCKET_LAUNCHER_COOLDOWN, ROCKET_LAUNCHER,
                                ter, range) {}


RocketLauncher::~RocketLauncher() {}




SoundWaves::SoundWaves(TerrainMap& ter, uint16_t range, Config* c/*, 
                        std::list<Command>& damageBroadcaster, Unit* self*/):
                                Weapon(c->SOUND_WAVES_DAMAGE,
                                c->SOUND_WAVES_COOLDOWN, SOUND_WAVES,
                                ter, range),
                                bonus(c->SOUND_WAVES_BONUS)//,
                                //damageBroadcaster(damageBroadcaster),
                                //self(self) 
                                {}

uint16_t SoundWaves::getDamageModForInfantry() {
    return this->bonus;
}

//void SoundWaves::areaAttack(Unit* objective) {
    //coor_t ownPos = this->self->getPosition();
    //coor_t objPos = objective->getPosition();
    //int vectorY = (int)objPos.first - (int)ownPos.first;
    //int vectorX = (int)objPos.second - (int)ownPos.second;
    //std::set<coor_t> attackedPos;
    //std::set<Unit*> attackedGuys;
    //uint16_t distance = abs(vectorY) + abs(vectorX);
    //double factor = sqrt(vectorY * vectorY + 
                         //vectorX * vectorX); 
    //double versorY = vectorY / factor;
    //double versorX = vectorX / factor;
    //for (double i = 0; i < distance; i++) {
        //double actY = versorY * i;
        //double actX = versorX * i;
        //for (int j = -2; j <= 2; j++) {
            //for (int k = -2; k < 2; k++)
                //attackedPos.insert(coor_t(ownPos.first + actY + j,
                                         //ownPos.second + actX + k));
        //}
    //}
    //for (Unit* u : attackedGuys) {
        //if (u->getID() == this->self->getID() || u->getID() == objective->getID()) 
            //continue;
        //u->damage(this->calculateDamage(u));
        //Command dam;
        //dam.add8bitsMessage(UNIT_ATTACKED);
        //dam.add16bitsMessage(0xFFFF);
        //dam.add16bitsMessage(u->getID());
        //dam.add16bitsMessage(u->getActualLife());
        //dam.add16bitsMessage(u->getTotalLife());
        //dam.add8bitsMessage(0xFF);
        //this->damageBroadcaster.push_back(dam);
    //}
//}


// TENERLO REPETIDO ACA ES ASQUEROSO PERO SE ENTREGA EN 5 HORAS
//void SoundWaves::areaAttack(Building* objective) {
    //coor_t ownPos = this->self->getPosition();
    //coor_t objPos = objective->getPosition();
    //int vectorY = (int)objPos.first - (int)ownPos.first;
    //int vectorX = (int)objPos.second - (int)ownPos.second;
    //std::set<coor_t> attackedPos;
    //std::set<Unit*> attackedGuys;
    //uint16_t distance = abs(vectorY) + abs(vectorX);
    //double factor = sqrt(vectorY * vectorY + 
                         //vectorX * vectorX); 
    //double versorY = vectorY / factor;
    //double versorX = vectorX / factor;
    //for (double i = 0; i < distance; i++) {
        //double actY = versorY * i;
        //double actX = versorX * i;
        //for (int j = -2; j <= 2; j++) {
            //for (int k = -2; k < 2; k++)
                //attackedPos.insert(coor_t(ownPos.first + actY + j,
                                         //ownPos.second + actX + k));
        //}
    //}
    //for (coor_t coord : attackedPos) {
        //Unit* act = this->terr.getUnit(coord);
        //if (act != nullptr)
            //attackedGuys.insert(act);
    //}
    //for (Unit* u : attackedGuys) {
        //if (u->getID() == this->self->getID()) 
            //continue;
        //u->damage(this->calculateDamage(u));
        //Command dam;
        //dam.add8bitsMessage(UNIT_ATTACKED);
        //dam.add16bitsMessage(0xFFFF);
        //dam.add16bitsMessage(u->getID());
        //dam.add16bitsMessage(u->getActualLife());
        //dam.add16bitsMessage(u->getTotalLife());
        //dam.add8bitsMessage(0xFF);
        //this->damageBroadcaster.push_back(dam);
    //}
//}



//bool SoundWaves::attack(Unit* objective) {
    //bool ret = Weapon::attack(objective);
    //if (ret)
        //this->areaAttack(objective);
    //return ret;
//}

//bool SoundWaves::attack(Building* objective) {
    //bool ret = Weapon::attack(objective);
    //if (ret)
        //this->areaAttack(objective);
    //return ret;
//}


SoundWaves::~SoundWaves() {}




TTCannon::TTCannon(TerrainMap& ter, uint16_t range, Config* c):
                                Weapon(c->TTCANNON_DAMAGE,
                                c->TTCANNON_COOLDOWN, TTCANNON,
                                ter, range),
                                bonus(c->TTCANNON_BONUS) {}

uint16_t TTCannon::getDamageModForVehicle() {
    return this->bonus;
}

uint16_t TTCannon::getDamageModForBuilding() {
    return this->bonus;
}

TTCannon::~TTCannon() {}



PlasmaCannon::PlasmaCannon(TerrainMap& ter, uint16_t range, Config* c):
                                Weapon(c->PLASMA_DAMAGE,
                                c->PLASMA_COOLDOWN, PLASMA,
                                ter, range),
                                bonus(c->PLASMA_BONUS) {}

uint16_t PlasmaCannon::getDamageModForVehicle() {
    return this->bonus;
}

uint16_t PlasmaCannon::getDamageModForBuilding() {
    return this->bonus;
}

PlasmaCannon::~PlasmaCannon() {}




TwoHanded::TwoHanded(TerrainMap& ter, uint16_t range, Config* c):
                                        Weapon(0, 0, 0xFF, ter, range), 
                                        weapons(std::pair<Weapon*, Weapon*>(
                                        new AssaultRifle(ter, range, c),
                                        new RocketLauncher(ter, range, c)
                                        )){}
void TwoHanded::update() {
    this->weapons.first->update();
    this->weapons.second->update();
}

uint16_t TwoHanded::getType() {
    return (this->usedFirst)? this->weapons.first->getType() :
                              this->weapons.second->getType();
}

bool TwoHanded::attack(Unit* objective) {
    this->weapons.first->stopAttack();
    this->weapons.second->stopAttack();
    this->usedFirst = (this->weapons.first->getDamageModifier(objective)
                    > 0); // Porque el Rocket Launcher no tiene bonificaciones
    Weapon* chosen = (this->usedFirst)? this->weapons.first : 
                                        this->weapons.second;
    chosen->startAttack();
    return chosen->attack(objective);
}

bool TwoHanded::attack(Building* objective) {
    this->weapons.first->stopAttack();
    this->weapons.second->stopAttack();
    this->usedFirst = (this->weapons.first->getDamageModifier(objective)
                    > 0); // Porque el Rocket Launcher no tiene bonificaciones
    Weapon* chosen = (this->usedFirst)? this->weapons.first : 
                                        this->weapons.second;
    chosen->startAttack();
    return chosen->attack(objective);
}

void TwoHanded::startAttack() {
    if (this->usedFirst)
        this->weapons.first->startAttack();
    else 
        this->weapons.second->startAttack();
}

void TwoHanded::stopAttack() {
    this->weapons.first->stopAttack();
    this->weapons.second->stopAttack();
}

TwoHanded::~TwoHanded() {
    delete this->weapons.first;
    delete this->weapons.second;
}


DeviatorLauncher::DeviatorLauncher(TerrainMap& ter, uint16_t range, Config* c,
                std::string owner, std::list<std::pair<uint16_t, std::string>>& swappedUnits):
                                Weapon(c->ROCKET_LAUNCHER_DAMAGE,
                                c->ROCKET_LAUNCHER_COOLDOWN, ROCKET_LAUNCHER,
                                ter, range),
                                swappedUnits(swappedUnits),
                                owner(owner) {}

bool DeviatorLauncher::attack(Unit* objective) {
    bool ret = Weapon::attack(objective);
    if (ret) {
        this->swappedUnits.push_back(
        std::pair<uint16_t, std::string>(objective->getID(),
                                         this->owner));
        objective->swapOwner(this->owner);
    }
    return ret;
}

DeviatorLauncher::~DeviatorLauncher() {}

