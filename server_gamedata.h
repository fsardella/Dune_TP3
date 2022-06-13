#ifndef __SERVER_GAMEDATA_H
#define __SERVER_GAMEDATA_H

#include "server_game.h"

class GameData {
    unsigned int players;
    unsigned int required;
	std::string game_name;

 public:
    GameData(Game& game);
    std::string get_name();
	int get_num_bytes();
	int get_participants();
	int get_required();
	~GameData();
};

#endif
