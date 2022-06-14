#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include <map> 
#include "common_socket.h"
#include "server_game.h"
#include "server_gameSet.h"
#include "server_listener.h"
#include "server_talker.h"
#include "server_inputguy.h"
#include "common_blockingqueue.h"
#include "server_game.h"

typedef std::map<std::string, Talker*> talkerMap_t;

class Server {
	GameSet gameSet;
    talkerMap_t talkers;
    Listener listener;
    BlockingQueue<Game> playableGames;
    InputGuy inputGuy;
 public:
	explicit Server(const char* service_port);
	void server_run();
	~Server();
};

#endif /*__SERVER_H__*/
