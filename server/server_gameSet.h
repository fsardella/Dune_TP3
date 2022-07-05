#ifndef __GAMESET_H__
#define __GAMESET_H__

#include "server_game.h"
#include "server_gamedata.h"
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <mutex>
#include <utility>
#include "common_blockingqueue.h"
#include "server_config.h"

#define GSSUCCESS 0
#define GSERROR 1

class GameSet {
	std::map<std::string, Game> games;
	std::mutex m;
    BlockingQueue<Game>& readyGames;

    bool game_exists(const std::string& game_name);
	bool game_complete(const std::string& game_name);
    //Game& get_game(const std::string& game_name);
 public:
	explicit GameSet(BlockingQueue<Game>& readyGames);
	int add_game(int house, int required, const std::string& game_name,
                 const std::string& playerName, const std::string& mapPath,
                 Config* c);
	int game_join(int house, const std::string& game_name,
                  const std::string& playerName);
	//void get_games_names(std::vector<std::string> *games_names);
	void list_games(std::vector<std::string> *games_names,
                    std::list<GameData> *games_aux);
	~GameSet();
    
    GameSet(const GameSet&) = delete;
    GameSet& operator=(const GameSet&) = delete;

    GameSet(GameSet&&);
    GameSet& operator=(GameSet&&);
};

#endif /*__GAMESET_H__*/
