#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include "server_player.h"
#include "server_terrain_map.h"

class Game {
	unsigned int required;
	std::string game_name;
	std::list<Player> participants;
    std::string yamlMapPath;

 public:
	Game(unsigned int num_required, const std::string& name, const std::string& yamlMapPath);
	void add_participant(const int& ID_house, const std::string& playerName);
	std::string get_name();
	int get_num_bytes();
	int get_participants();
	int get_required();
	bool game_complete();
	~Game();
    
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&);
    Game& operator=(Game&&);
};


#endif /*__GAME_H__*/
