#ifndef __SERVER_GAMEHANDLER_H__
#define __SERVER_GAMEHANDLER_H__

#include "common_thread.h"
#include "server_game.h"
#include "server_activegame.h"
#include "common_command.h"
#include "common_blockingqueue.h"
#include "server_talker.h"
#include "server_broadcaster.h"
#include "server_timewizard.h"
#include "server_playerdata.h"
#include <map>

typedef std::map<std::string, Talker*> talkerMap_t;
typedef std::map<std::string, BlockingQueue<Command>> queueMap_t;

class GameHandler: public Thread {
    ActiveGame game;
    BlockingQueue<Command> commandQueue;
    queueMap_t playersQueue;
    bool ended = false;
    
    void processCommand(Command comm);
    void disconnect(Command comm);
    void addNewUnit(Command comm);
    void notifyError(Command comm);
    void notifySuccess(Command comm);
    
 public:
    GameHandler(Game newGame, talkerMap_t& talkerThreads);
    void run() override;
    bool endedRun();
	~GameHandler() override;
};







#endif
