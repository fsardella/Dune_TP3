#ifndef __TALKER_H__
#define __TALKER_H__

#include "server_game.h"
#include "server_gameSet.h"
#include "common_thread.h"
#include "server_protocol.h"
#include <string>

#include "common_blockingqueue.h"
#include "common_command.h"
#include "server_sender.h"
#include "server_playerdata.h"
#include <atomic>

#ifndef CLIENTOPERS
#define CLIENTOPERS
enum clientOpers {
    XXXX = 0,
    UNIRSE,
    LISTAR,
    CREAR, // Estan en espaniol porque asi era el tp de threads. Too bad!
    DISCONNECT,
    NEW_UNIT,
    NEW_BUILDING,
    ATTACK,
    MOVE,
    ADD_BUILDING
    
};
#endif

class Talker: public Thread {
    ProtocolServer protocol;
    BlockingQueue<Command>* commandQueue;
    Sender* sender;
    std::atomic<bool> finish = false;
    GameSet *gameSet;
    std::string playerName;
    
    
    void handleLobby(int operation);
    void handleGame(int operation);
    int create_game(int house, int required, const std::string& game_name,
                    const std::string& mapPath);
    void list_games();
    void list_maps();
    int join_game(int house, std::string& game_name);
 public:
    bool finishedThread();
    std::string getPlayerName();
    void startPlaying(BlockingQueue<Command>* newGameQueue,
                      sketch_t gameMap, std::list<PlayerData> players,
                      BlockingQueue<Command>& sendingQueue);
	explicit Talker(Socket&& socket, GameSet* game_set);
	void run() override;
	~Talker() override;
};

#endif /*__TALKER_H__*/
