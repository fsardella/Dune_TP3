#include "server_activegame.h"
#include "server_units.h"
#include "server_buildings.h"

#include <vector>
#include <utility>
#include <iostream>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

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


ActiveGame::ActiveGame(Game game, Config* c): c(c),
                                   buildingIDCount(game.get_required()), 
                                   game(std::move(game)),
                                   adorableLittleWorm(Worm(this->gameMap, c->WORM_DELAY)){
    YAML::Node node = YAML::LoadFile(c->MAP_PATHS + this->game.getMapPath() + ".yaml");
    this->gameMapSketch = node["matrix"].as<std::vector<std::vector<int>>>();
    this->gameMap = TerrainMap(this->gameMapSketch);
}

bool ActiveGame::hasUnit(uint16_t unitID) {
    return (this->unitIDs.find(unitID) != this->unitIDs.end());
}

bool ActiveGame::hasBuilding(uint16_t buildingID) {
    return (this->buildingIDs.find(buildingID) != this->buildingIDs.end());
}


std::list<PlayerData> ActiveGame::getPlayersData() {
    lock_t lock(this->m);
    std::list<PlayerData> ret = this->game.buildBases(this->gameMap);
    uint16_t id = 0;
    for (PlayerData& p : ret) {
        this->game.setPlayerID(p.name, id);
        this->buildingIDs[id] = p.name;
        id ++;
    }
    return ret;
}

sketch_t ActiveGame::getMapSketch() {
    return this->gameMapSketch;
    // No tiene mutex porque gameMapSketch solo cambia en
    // el constructor.
}

void ActiveGame::endGame() {
    lock_t lock(this->m);
    this->alive = false;
}

bool ActiveGame::isAlive() {
    lock_t lock(this->m);
    return this->alive;
}

void ActiveGame::updateUnitsBuffer() {
    std::list<UnitBuffer>::iterator it = unitsBuilding.begin();
    coor_t validDir;
    uint16_t factor;
    while (it != unitsBuilding.end()) {
        if (!this->game.isPlaying(it->getPlayerName())) {
            it = unitsBuilding.erase(it);
            continue;
        }
        factor = this->game.getUnitFactor(it->getPlayerName(), it->getType());
        if (factor == 0) {
            it = unitsBuilding.erase(it);
            continue;
        }
        if (it->willItEnd(factor)) {
            validDir = this->game.getUnitDir(it->getPlayerName(), it->getType(),
                                             this->gameMap);
            if (validDir == coor_t(0,0)) {
                std::cout << "invalid dir\n";
                continue;
            }
            this->game.addUnit(it->getPlayerName(),
                               it->getResult(validDir, this->unitIDCount));
            this->unitIDs[this->unitIDCount] = it->getPlayerName();
            this->unitIDCount++;
            it = unitsBuilding.erase(it);
        } else {
            it->process(factor);
            it++;
        }
    
    }
}

std::map<uint8_t, std::list<UnitData>> ActiveGame::getUnits() {
    return this->game.getUnits();
}


std::list<Command> ActiveGame::receiveEvents() {
    std::list<Command> ret(this->events); // Copy list
    this->events.clear();
    return ret;
}


std::list<UnitBuffer> ActiveGame::receiveUnitBuffer() {
    std::list<UnitBuffer> ret(this->unitsBuilding); // Copy list
    return ret;
}

std::list<Command> ActiveGame::receiveBuildingsBuilding() {
    std::list<Command> ret;
    std::map<uint8_t, std::pair<uint8_t, uint8_t>> result;
    this->game.getBuildingsBuilding(result);
    for (auto& c : result) {
        Command comm;
        comm.add8BytesMessage(BUILDING_WIP);
        comm.setType(BUILDING_WIP);
        comm.changeSender(this->buildingIDs[c.first]);
        comm.add8BytesMessage(c.second.first);
        comm.add8BytesMessage(c.second.second);
        ret.push_back(comm);
    }
    return ret;
}

std::map<uint8_t, std::pair<uint32_t, int32_t>> ActiveGame::getPlayersResources() {
    return this->game.getPlayersResources();
}

std::list<std::pair<coor_t, uint16_t>> ActiveGame::getMenageData() {
    std::list<std::pair<coor_t, uint16_t>> ret;
    this->gameMap.addMenageData(ret);
    return ret;
}

broadcast_t ActiveGame::getBroadcast() {
    lock_t lock(this->m);
    return broadcast_t(this->getUnits(),
                       this->getPlayersResources(),
                       this->receiveEvents(),
                       this->receiveUnitBuffer(),
                       this->receiveBuildingsBuilding(),
                       this->getMenageData());
}


void ActiveGame::update() {
    lock_t lock(this->m);
    //std::cout << "Updating units buffer\n";
    this->updateUnitsBuffer();
    //std::cout << "Updating units\n";
    this->game.updateUnits(this->events);
    //std::cout << "Updating buildings\n";
    this->game.updateBuildings();
    //std::cout << "Cleaning corpses\n";
    this->adorableLittleWorm.update(this->events);
    this->game.cleanCorpses(this->unitIDs, this->buildingIDs, this->events);
}

void ActiveGame::addUnit(std::string playerName, uint8_t type) {
    lock_t lock(this->m);
    for (UnitBuffer& un : this->unitsBuilding) {
        if (playerName == un.getPlayerName() && type == un.getType()) 
            return;
    }
    bool ret = this->game.chargeMoney(playerName, type);
    if (ret)
        this->unitsBuilding.push_back(UnitBuffer(type, playerName, this->gameMap,
                                             this->game.getPlayerID(playerName), 
                                             c, this->events));
}

void ActiveGame::createBuilding(std::string playerName, uint8_t type) {
    lock_t lock(this->m);
    this->game.createBuilding(playerName, type);
}

bool ActiveGame::addBuilding(std::string playerName, uint16_t x, uint16_t y) {
    lock_t lock(this->m);
    uint16_t ret = this->game.addBuilding(playerName, x, y,
                                      this->gameMap, this->buildingIDCount);
    if (ret != 0xFFFF) {
        Command newEvent;
        newEvent.add8BytesMessage(BUILDING_BUILT);
        newEvent.setType(BUILDING_BUILT);
        newEvent.add8BytesMessage(this->game.getPlayerID(playerName));
        newEvent.add16BytesMessage(this->buildingIDCount);
        newEvent.add8BytesMessage(ret);
        newEvent.add16BytesMessage(x);
        newEvent.add16BytesMessage(y);
        this->events.push_back(newEvent);
        this->buildingIDs[this->buildingIDCount] = playerName;
        this->buildingIDCount++;
    }
    return (ret != 0xFFFF);
}

void ActiveGame::destroyBuilding(std::string playerName, uint16_t id) {
    lock_t lock(this->m);
    game.destroyBuilding(playerName, id, this->events);
}

void ActiveGame::moveUnit(std::string playerName, uint16_t unitID, uint16_t x,
                          uint16_t y) {
    lock_t lock(this->m);
    this->game.moveUnit(playerName, unitID, coor_t(y, x));
}


void ActiveGame::attackUnit(uint16_t attacker, uint16_t attackedUnit) {
    lock_t lock(this->m);
    if (!this->hasUnit(attacker) || !this->hasUnit(attackedUnit))
        return;
    Unit* atta = this->game.getUnit(unitIDs[attacker], attacker);
    Unit* attad = this->game.getUnit(unitIDs[attackedUnit], attackedUnit);
    if (atta == nullptr || attad == nullptr)
        return;
    atta->attack(attad);
}


void ActiveGame::attackBuilding(uint16_t attacker, uint16_t attackedBuilding) {
    lock_t lock(this->m);
    if (!this->hasUnit(attacker) || !this->hasBuilding(attackedBuilding))
        return;
    Unit* atta = this->game.getUnit(unitIDs[attacker], attacker);
    Building* attad = this->game.getBuilding(buildingIDs[attackedBuilding],
                                             attackedBuilding);
    if (atta == nullptr || attad == nullptr)
        return;
    atta->attack(attad);
}

void ActiveGame::disconnect(std::string disconnected) {
    lock_t lock(this->m);
    this->game.disconnect(disconnected, this->events);
}
                  

//std::list<std::string> ActiveGame::getPlayerNames() {
    //lock_t lock(this->m);
    //return this->game.getPlayerNames(this->gameMap);
//}


ActiveGame::~ActiveGame() {}
