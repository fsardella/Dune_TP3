#include "server_activegame.h"
#include "server_units.h"
#include "server_buildings.h"

#include <vector>
#include <utility>

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
    BUILDING_WIP
};
#endif


ActiveGame::ActiveGame(Game game): buildingIDCount(game.get_required()), 
                                   game(std::move(game)) {
    sketch_t fours;
    for (int i = 0; i < 40; i++) {
        std::vector<int> row;
        for (int j = 0; j < 40; j++) {
            row.push_back(4);
        }
        fours.push_back(row);
    }
    this->gameMapSketch = fours;
    this->gameMap = TerrainMap(this->gameMapSketch); // DEBUG, use YAML
    // TerrainMap va a ser mas inteligente y traducir los id
    // de tiles a cada tipo de terreno.
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
    sketch_t rocks;
    for (int i = 0; i < 40; i++) {
        std::vector<int> row;
        for (int j = 0; j < 40; j++) {
            row.push_back(6);
        }
        rocks.push_back(row);
    }
    return rocks;
    // return this->gameMapSketch
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
        if (it->willItEnd(factor)) {
            validDir = this->game.getUnitDir(it->getPlayerName(), it->getType(),
                                             this->gameMap);
            if (validDir == coor_t(0,0))
                continue;
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

broadcast_t ActiveGame::getBroadcast() {
    lock_t lock(this->m);
    return broadcast_t(this->getUnits(),
                       this->getPlayersResources(),
                       this->receiveEvents(),
                       this->receiveUnitBuffer(),
                       this->receiveBuildingsBuilding());
}

void ActiveGame::update() {
    lock_t lock(this->m);
    this->updateUnitsBuffer();
    this->game.updateUnits();
    this->game.updateBuildings();
    //this->game.cleanCorpses();
}

void ActiveGame::addUnit(std::string playerName, uint8_t type) {
    lock_t lock(this->m);
    bool ret = this->game.chargeMoney(playerName, type);
    if (ret)
        this->unitsBuilding.push_back(UnitBuffer(type, playerName, this->gameMap,
                                             this->game.getPlayerID(playerName)));
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
        newEvent.add16BytesMessage(x);
        this->events.push_back(newEvent);
        this->buildingIDs[this->buildingIDCount] = playerName;
        this->buildingIDCount++;
    }
    return (ret != 0xFFFF);
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
                  

//std::list<std::string> ActiveGame::getPlayerNames() {
    //lock_t lock(this->m);
    //return this->game.getPlayerNames(this->gameMap);
//}


ActiveGame::~ActiveGame() {}
