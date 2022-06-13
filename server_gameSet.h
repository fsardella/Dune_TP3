#ifndef __GAMESET_H__
#define __GAMESET_H__

#include "server_game.h"
#include "server_gamedata.h"
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <mutex>

#define SUCCESS 0
#define ERROR 1

class GameSet {
	std::vector<Game> games;
	std::mutex m;
    
    Game& get_game(const std::string& game_name);
 public:
	GameSet();
	int add_game(int house, int required, const std::string& game_name,
                 const std::string& playerName, const std::string& mapPath);
	bool game_exists(const std::string& game_name);
	bool game_complete(const std::string& game_name);
	int game_join(int house, const std::string& game_name, const std::string& playerName);
	void get_games_names(std::vector<std::string> *games_names);
	void list_games(std::vector<std::string> *games_names, std::list<GameData> *games_aux);
	~GameSet();
};

#endif /*__GAMESET_H__*/
