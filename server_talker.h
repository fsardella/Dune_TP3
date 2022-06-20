#ifndef __TALKER_H__
#define __TALKER_H__

#include "server_game.h"
#include "server_gameSet.h"
#include "common_thread.h"
#include "server_protocol.h"
#include <string>

#include "common_blockingqueue.h"
#include "server_command.h"
#include "server_sender.h"

#define CREAR 3
#define UNIRSE 1
#define LISTAR 2
#define DISCONNECT 3
#define NEW_UNIT 5

class Talker: public Thread {
    ProtocolServer protocol;
    BlockingQueue<Command>* commandQueue;
    Sender* sender;
    bool finish = false;
    GameSet *gameSet;
    std::string playerName;
    
    int create_game(int house, int required, const std::string& game_name,
                    const std::string& mapPath);
    void list_games();
    void list_maps();
    int join_game(int house, std::string& game_name);
 public:
    bool finishedThread();
    std::string getPlayerName();
    void startPlaying(BlockingQueue<Command>* newGameQueue,
                      sketch_t gameMap, BlockingQueue<Command>& sendingQueue);
	explicit Talker(Socket&& socket, GameSet* game_set);
	void run() override;
	~Talker() override;
};

#endif /*__TALKER_H__*/
