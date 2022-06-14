#ifndef __TALKER_H__
#define __TALKER_H__

#include "server_game.h"
#include "server_gameSet.h"
#include "common_thread.h"
#include "server_protocol.h"
#include <string>

#define CREAR 3
#define UNIRSE 1
#define LISTAR 2

class Talker: public Thread {
    ProtocolServer protocol;
    bool finish = false;
    GameSet *gameSet;
    std::string playerName;
    
    int create_game(int house, int required, const std::string& game_name,
                    const std::string& mapPath);
    void list_games();
    int join_game(int house, std::string& game_name);
 public:
    bool finishedThread();
    std::string getPlayerName();
	explicit Talker(Socket&& socket, GameSet* game_set);
	void run() override;
	~Talker() override;
};

#endif /*__TALKER_H__*/
