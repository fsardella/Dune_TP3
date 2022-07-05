#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "common_socket.h"
#include "server_game.h"
#include "server_gameSet.h"
#include "common_thread.h"
#include "server_talker.h"
#include "server_config.h"
#include <list>

typedef std::map<std::string, Talker*> talkerMap_t;

class Listener: public Thread {
    Config* c;
    Socket socket_original;
    talkerMap_t& clientTalkers;
    bool listening;
    void cleanFinishedHandlers();
    GameSet *gameSet;
 public:
	explicit Listener(const char* service_port, GameSet *gameSet,
                      talkerMap_t& clientTalkers, Config* c);
    void stopListening(); 
	void run() override;
	~Listener() override;
};

#endif /*__LISTENER_H__*/
