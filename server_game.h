#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <string>
#include "server_player.h"
#include "server_terrain_map.h"

typedef std::pair<uint16_t, uint16_t> coor_t;

class Game {
	unsigned int required;
	std::string game_name;
	std::map<std::string, Player> participants;
    std::string yamlMapPath;
    
    bool isPlaying(std::string playerName);
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
    void addUnit(std::string playerName, int x, int y, TerrainMap& terr);
    std::map<std::string, std::list<coor_t>> getUnits();
    std::list<std::string> getPlayerNames();
	~Game();
    
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&);
    Game& operator=(Game&&);
};


#endif /*__GAME_H__*/
