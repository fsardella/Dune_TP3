#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <list>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include "server_player.h"
#include "server_terrain_map.h"
#include "server_unitdata.h"
#include "server_playerdata.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

class Game {
	unsigned int required;
	std::string game_name;
	std::map<std::string, Player> participants;
    std::string yamlMapPath;
    std::list<coor_t> basesCoordinates;
 public:
	Game(unsigned int num_required, const std::string& name, const std::string& yamlMapPath);
    Game(); // Not intended for use
	void add_participant(const int& ID_house, const std::string& playerName);
	std::string get_name() const;
	int get_num_bytes() const;
	int get_participants() const;
	int get_required() const;
	bool game_complete() const;
    
    int getHouse(std::string playerName);
    uint8_t getPlayerID(std::string playerName);
    
    bool isPlaying(std::string playerName);
    uint8_t getUnitFactor(std::string playerName, uint8_t type);
    coor_t getUnitDir(std::string playerName, uint8_t type, TerrainMap& terr);
    bool addUnit(std::string playerName, Unit* unit, uint8_t id);
    void moveUnit(std::string playerName, uint16_t unitID, coor_t coor);
    void updateUnits();
    bool addBuilding(std::string playerName, uint8_t type,
                 uint16_t x, uint16_t y, TerrainMap& terr,
                 uint16_t id);
    std::map<uint8_t, std::list<UnitData>> getUnits();
    std::list<PlayerData> buildBases(TerrainMap& terr);
	void setPlayerID(std::string playerName, uint8_t id);
    ~Game();
    
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&);
    Game& operator=(Game&&);
};


#endif /*__GAME_H__*/
