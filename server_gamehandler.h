#ifndef __SERVER_GAMEHANDLER_H__
#define __SERVER_GAMEHANDLER_H__

#include "common_thread.h"
#include "server_game.h"
#include "server_activegame.h"
#include "server_command.h"
#include "common_blockingqueue.h"
#include <map>

typedef std::map<std::string, Talker*> talkerMap_t;

class GameHandler: public Thread {
    ActiveGame game;
    BlockingQueue<Command> commandQueue;
    talkerMap_t& talkerThreads;
 public:
    GameHandler(Game newGame, talkerMap_t& talkerThreads);
    void run() override;
	~GameHandler() override;
};







#endif
