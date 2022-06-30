#include "server_buildings.h"


Building::Building(coor_t size, uint16_t totalLife):
                   size(size),
                   actualLife(totalLife),
                   totalLife(totalLife) {}

coor_t Building::getPosition() {
    return this->position;
}

coor_t Building::getSize() {
    return this->size;
}

uint16_t Building::getID() {
    return this->buildingID;
}

bool Building::isLightFactory() {
    return false;
}

uint16_t Building::getActualLife() {
    return this->actualLife;
}

uint16_t Building::getTotalLife() {
    return this->totalLife;
}

bool Building::canBuild(TerrainMap& terr, coor_t position) {
    return terr.canBuild(position, this->size);
}

void Building::build(TerrainMap& terr, coor_t position, uint16_t id) {
    this->buildingID = id;
    this->position = position;
    return terr.build(position, this);
}

void Building::attack(uint16_t damage) {
    this->actualLife = (damage < actualLife)? actualLife - damage : 0;
}
    
bool Building::destroyed() {
    return (this->actualLife == 0);
}

void Building::watch() {
    this->watchers++;    
}

void Building::stopWatching() {
    if (this->canBeCleaned())
        return;
    this->watchers--;   
}

bool Building::canBeCleaned() {
    return (this->watchers == 0);
}


Building::~Building() {}



Base::Base(coor_t position): Building(coor_t(3, 3), 3000) {
    this->position = position;
}

Base::~Base() {}


LightFactory::LightFactory(): Building(coor_t(3, 3), 500) {} 

bool LightFactory::isLightFactory() {
    return true;
}

LightFactory::~LightFactory() {}
