#ifndef __SERVER_ACTIVEGAME_H__
#define __SERVER_ACTIVEGAME_H__


#include <mutex>
#include <map>
#include <string>
#include <list>
#include "server_game.h"
#include "server_terrain_map.h"

typedef std::lock_guard<std::mutex> lock_t;
typedef std::vector<std::vector<int>> sketch_t;
typedef std::pair<uint16_t, uint16_t> coor_t;

class ActiveGame {
    Game game;
    TerrainMap gameMap;
    std::mutex m;
    bool alive = true;
    
    int getHouse(std::string playerName);
 public:
    ActiveGame(Game game);
    sketch_t getMapSketch();
    std::list<std::string> getPlayerNames();
    void endGame();
    bool isAlive();
    bool addUnit(std::string playerName, int x, int y); // TODO agregar mas tipos de unidades
    std::map<std::string, std::list<UnitData>> getUnits();
    ~ActiveGame();
};


#endif
