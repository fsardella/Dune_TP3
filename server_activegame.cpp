#include "server_activegame.h"

#include <vector>
#include <utility>

ActiveGame::ActiveGame(Game game): game(std::move(game)) {
    sketch_t ones;
    for (int i = 0; i <= 40; i++) {
        std::vector<int> row;
        for (int j = 0; j <= 40; j++) {
            row.push_back(1);
        }
        ones.push_back(row);
    } 
    this->gameMap = TerrainMap(ones); // DEBUG, use YAML
}

int ActiveGame::getHouse(std::string playerName) {
    return this->game.getHouse(playerName);
}



sketch_t ActiveGame::getMapSketch() {
    // Lee el YAML en this->game
    sketch_t sands;
    for (int i = 0; i <= 40; i++) {
        std::vector<int> row;
        for (int j = 0; j <= 40; j++) {
            row.push_back(0);
        }
        ones.push_back(row);
    }
    return sands;
}

void ActiveGame::endGame() {
    this->alive = false;
}

bool ActiveGame::isAlive() {
    return this->alive;
}

void ActiveGame::addUnit(std::string playerName, int x, int y) {
    lock_t lock(this->m);
    //this->game.addUnit(std::string playerName, int x, int y, TerrainMap& terr);
    this->game.addUnit(playerName, x, y, this->gameMap);
}


std::list<std::string> ActiveGame::getPlayerNames() {
    this->game.getPlayerNames();
}

std::map<std::string, std::list<coor_t>>
    ActiveGame::getUnits(std::map<std::string, int>& houses) {
    lock_t lock(this->m);
    std::map<std::string, std::list<coor_t>> ret = this->game.getUnits();
    for (const auto& u: ret) {
        houses[u.first] = this->getHouse(u.first);
    }
    return ret;
}

ActiveGame::~ActiveGame() {}
