#ifndef __TALKER_H__
#define __TALKER_H__

#include "server_game.h"
#include "server_gameSet.h"
#include "common_thread.h"
#include "server_protocol.h"
#include <string>

#include "common_blockingqueue.h"
#include "server_command.h"

#define CREAR 3
#define UNIRSE 1
#define LISTAR 2
#define NEW_UNIT 5

class Talker: public Thread {
    ProtocolServer protocol;
    bool startedPlaying = false;
    bool finish = false;
    GameSet *gameSet;
    std::string playerName;
    BlockingQueue<Command>* commandQueue;
    
    int create_game(int house, int required, const std::string& game_name,
                    const std::string& mapPath);
    void list_games();
    int join_game(int house, std::string& game_name);
 public:
    bool finishedThread();
    std::string getPlayerName();
    void startPlaying(BlockingQueue<Command>* newGameQueue,
                              sketch_t gameMap);
    void sendUnits(std::map<std::string, std::list<coor_t>> units,
                       std::map<std::string, int> houses);
                       
	explicit Talker(Socket&& socket, GameSet* game_set);
	void run() override;
	~Talker() override;
};

#endif /*__TALKER_H__*/
