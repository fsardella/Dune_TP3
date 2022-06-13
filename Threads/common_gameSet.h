#ifndef __GAMESET_H__
#define __GAMESET_H__

#include "common_game.h"
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
	public:
	GameSet();
	int add_game(int house, int required, std::string& game_name);
	bool game_exists(std::string& game_name);
	bool game_complete(std::string& game_name);
	int game_join(std::string& game_name);
	void get_games_names(std::vector<std::string> *games_names);
	Game get_game(std::string& game_name);
	void list_games(std::vector<std::string> *games_names, std::list<Game> *games_aux);
	~GameSet();
};

#endif /*__GAMESET_H__*/
