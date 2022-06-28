#ifndef __SERVER_ACTIVEGAME_H__
#define __SERVER_ACTIVEGAME_H__


#include <mutex>
#include <map>
#include <set>
#include <string>
#include <list>
#include "server_game.h"
#include "server_terrain_map.h"
#include "server_playerdata.h"
#include "common_command.h"
#include "server_unitbuffer.h"

typedef std::lock_guard<std::mutex> lock_t;
typedef std::vector<std::vector<int>> sketch_t;
typedef std::pair<uint16_t, uint16_t> coor_t;

class ActiveGame {
    uint16_t unitIDCount = 0;
    uint16_t buildingIDCount;
    Game game;
    sketch_t gameMapSketch;
    TerrainMap gameMap;
    std::mutex m;
    bool alive = true;
    std::map<uint16_t, std::string> unitIDs;
    std::map<uint16_t, std::string> buildingIDs;
    std::list<UnitBuffer> unitsBuilding;
    std::list<Command> events;
    
    bool hasUnit(uint16_t unitID);
    bool hasBuilding(uint16_t buildingID);
    void updateUnitsBuffer();
    //int getHouse(std::string playerName);
 public:
    ActiveGame(Game game);
    sketch_t getMapSketch();
    std::list<PlayerData> getPlayersData(); // ONLY CALL ONCE
    std::list<Command> receiveEvents();
    std::list<UnitBuffer> receiveUnitBuffer();
    void update();
    void endGame();
    bool isAlive();
    void addUnit(std::string playerName, uint8_t type);
    bool addBuilding(std::string playerName, uint8_t type, uint16_t x,
                     uint16_t y);
    void moveUnit(std::string playerName, uint16_t unitID, uint16_t x,
                  uint16_t y);
    void attackUnit(uint16_t attacker, uint16_t attackedUnit);
    void attackBuilding(uint16_t attacker, uint16_t attackedBuilding);
                  
    std::map<uint8_t, std::list<UnitData>> getUnits();
    ~ActiveGame();
};


#endif
