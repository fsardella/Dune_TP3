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
#include "server_units.h"
#include "server_buildings.h"
#include "common_command.h"
#include "server_config.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

class Game {
    Config* c;
	unsigned int required;
	std::string game_name;
	std::map<std::string, Player> participants;
    std::string yamlMapPath;
    std::list<coor_t> basesCoordinates;
    
    bool decidedWinner = false;
 public:
	Game(unsigned int num_required, const std::string& name, const std::string& yamlMapPath,
         Config* c);
    Game(); // Not intended for use
	void add_participant(const int& ID_house, const std::string& playerName);
	std::string get_name() const;
    std::string getMapPath();
	int get_num_bytes() const;
	int get_participants() const;
	int get_required() const;
	bool game_complete() const;
    
    int getHouse(std::string playerName);
    uint8_t getPlayerID(std::string playerName);
    
    Unit* getUnit(std::string playerName, uint16_t unitID);
    Building* getBuilding(std::string playerName, uint16_t buildingID);
    
    
    bool chargeMoney(std::string playerName, uint8_t type);
    bool isPlaying(std::string playerName);
    uint8_t getUnitFactor(std::string playerName, uint8_t type);
    coor_t getUnitDir(std::string playerName, uint8_t type, TerrainMap& terr);
    bool addUnit(std::string playerName, Unit* unit);
    void moveUnit(std::string playerName, uint16_t unitID, coor_t coor);

    void destroyBuilding(std::string playerName, uint16_t id,
                         std::list<Command>& events);
    void updateUnits(std::list<Command>& events);
    void swapUnits(std::string previousOwner,
                   std::string newOwner, uint16_t id);
    void updateBuildings();
    void cleanCorpses(std::map<uint16_t, std::string>& unitIDs,
                      std::map<uint16_t, std::string>& buildingIDs,
                      std::list<Command>& events);

    uint16_t addBuilding(std::string playerName,
                 uint16_t x, uint16_t y, TerrainMap& terr,
                 uint16_t id);
    void createBuilding(std::string playerName, uint8_t type);
    std::map<uint8_t, std::list<UnitData>> getUnits();
    std::map<uint8_t, std::pair<uint32_t, int32_t>> getPlayersResources();
    void getBuildingsBuilding(std::map<
                                uint8_t,
                                std::pair<uint8_t, uint8_t>>& buildingInfo);
    std::list<PlayerData> buildBases(TerrainMap& terr);
	void setPlayerID(std::string playerName, uint8_t id);
    void disconnect(std::string disconnected, std::list<Command>& events);
    ~Game();
    
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&);
    Game& operator=(Game&&);
};


#endif /*__GAME_H__*/
