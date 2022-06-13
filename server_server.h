#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector> 
#include "common_socket.h"
#include "server_game.h"
#include "server_gameSet.h"
#include "server_listener.h"

class Server {
	GameSet gameSet;
    Listener listener;
    public:
	explicit Server(const char* service_port);
	void server_run();
	~Server();
};

#endif /*__SERVER_H__*/
