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
        sands.push_back(row);
    }
    return sands;
}

void ActiveGame::endGame() {
    this->alive = false;
}

bool ActiveGame::isAlive() {
    return this->alive;
}

bool ActiveGame::addUnit(std::string playerName, int x, int y) {
    // Hagan monitores, no dejen locks sueltos. Es la manera de no tener race conditions y no es difícil.
    lock_t lock(this->m);
    if (this->gameMap.isOccupied(coor_t(y, x)))
        return false;
    this->game.addUnit(playerName, x, y, this->gameMap);
    return true;
}


std::list<std::string> ActiveGame::getPlayerNames() {
    return this->game.getPlayerNames();
}

std::map<std::string, std::list<UnitData>> ActiveGame::getUnits() {
    lock_t lock(this->m);
    return this->game.getUnits();
}

ActiveGame::~ActiveGame() {}
