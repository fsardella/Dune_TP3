#include "server_activegame.h"

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
    UNIT_WIP
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

int ActiveGame::getHouse(std::string playerName) {
    lock_t lock(this->m);
    return this->game.getHouse(playerName);
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

std::list<Command> ActiveGame::receiveEvents() {
    lock_t lock(this->m);
    std::list<Command> ret(this->events); // Copy list
    this->events.clear();
    return ret;
}


std::list<UnitBuffer> ActiveGame::receiveUnitBuffer() {
    lock_t lock(this->m);
    std::list<UnitBuffer> ret(this->unitsBuilding); // Copy list
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
            this->game.addUnit(it->getPlayerName(), it->getResult(validDir),
                               this->unitIDCount);
            this->unitIDs[this->unitIDCount] = it->getPlayerName();
            this->unitIDCount++;
            it = unitsBuilding.erase(it);
        } else {
            it->process(factor);
            it++;
        }
    
    }
}

void ActiveGame::update() {
    lock_t lock(this->m);
    this->updateUnitsBuffer();
    this->game.updateUnits();
}

void ActiveGame::addUnit(std::string playerName, uint8_t type) {
    lock_t lock(this->m);
    this->unitsBuilding.push_back(UnitBuffer(type, playerName, this->gameMap,
                                             this->game.getPlayerID(playerName)));
}

bool ActiveGame::addBuilding(std::string playerName, uint8_t type, uint16_t x, uint16_t y) {
    lock_t lock(this->m);
    bool ret = this->game.addBuilding(playerName, type,
                              x, y, this->gameMap, this->buildingIDCount);
    if (ret) {
        Command newEvent;
        newEvent.add8BytesMessage(BUILDING_BUILT);
        newEvent.add8BytesMessage(this->game.getPlayerID(playerName));
        newEvent.add16BytesMessage(this->buildingIDCount);
        newEvent.add8BytesMessage(type);
        newEvent.add16BytesMessage(x);
        newEvent.add16BytesMessage(x);
        this->events.push_back(newEvent);
        this->buildingIDCount++;
    }
    return ret;
}

void ActiveGame::moveUnit(std::string playerName, uint16_t unitID, uint16_t x,
                          uint16_t y) {
    this->game.moveUnit(playerName, unitID, coor_t(y, x));
}
//std::list<std::string> ActiveGame::getPlayerNames() {
    //lock_t lock(this->m);
    //return this->game.getPlayerNames(this->gameMap);
//}

std::map<uint8_t, std::list<UnitData>> ActiveGame::getUnits() {
    lock_t lock(this->m);
    return this->game.getUnits();
}

ActiveGame::~ActiveGame() {}
