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
    Game(); // Not intended for use
	void add_participant(const int& ID_house, const std::string& playerName);
	std::string get_name() const;
	int get_num_bytes() const;
	int get_participants() const;
	int get_required() const;
	bool game_complete() const;
	~Game();
    
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&);
    Game& operator=(Game&&);
};


#endif /*__GAME_H__*/
