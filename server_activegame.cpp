#include "server_activegame.h"

#include <vector>
#include <utility>

ActiveGame::ActiveGame(Game game): game(std::move(game)) {
    sketch_t ones;
    for (int i = 0; i < 40; i++) {
        std::vector<int> row;
        for (int j = 0; j < 40; j++) {
            row.push_back(1);
        }
        ones.push_back(row);
    } 
    this->gameMap = TerrainMap(ones); // DEBUG, use YAML
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
        this->playerIDs[id] = p.name;
        this->buildingIDs[id] = p.name;
        id ++;
    }
    return ret;
}


sketch_t ActiveGame::getMapSketch() {
    // Lee el YAML en this->game
    sketch_t rocks;
    for (int i = 0; i < 40; i++) {
        std::vector<int> row;
        for (int j = 0; j < 40; j++) {
            row.push_back(6);
        }
        rocks.push_back(row);
    }
    return rocks;
}

void ActiveGame::endGame() {
    lock_t lock(this->m);
    this->alive = false;
}

bool ActiveGame::isAlive() {
    lock_t lock(this->m);
    return this->alive;
}

bool ActiveGame::addUnit(std::string playerName, int x, int y) {
    lock_t lock(this->m);
    if (this->gameMap.isOccupied(coor_t(y, x)))
        return false;
    this->game.addUnit(playerName, x, y, this->gameMap);
    return true;
}


//std::list<std::string> ActiveGame::getPlayerNames() {
    //lock_t lock(this->m);
    //return this->game.getPlayerNames(this->gameMap);
//}

std::map<std::string, std::list<UnitData>> ActiveGame::getUnits() {
    lock_t lock(this->m);
    return this->game.getUnits();
}

ActiveGame::~ActiveGame() {}
