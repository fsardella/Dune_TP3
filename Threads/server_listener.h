#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "common_socket.h"
#include "common_game.h"
#include "common_gameSet.h"
#include "server_thread.h"
#include "server_talker.h"
#include <list>

class Listener: public Thread {
    Socket socket_original;
    std::list<Talker *> clientsTalkers;
    void cleanFinishedHandlers();
    GameSet *gameSet;
    public:
	explicit Listener(const char* service_port, GameSet *gameSet);
	void run() override;
	~Listener() override;
};

#endif /*__LISTENER_H__*/