#ifndef __SERVERRECEIVER_H__
#define __SERVERRECEIVER_H__

#include "GameView.h"
#include "Drawer.h"
#include "thread.h"
#include "client_protocol.h"

class ServerReceiver: public Thread {
	Drawer* drawer;
	GameView* gameView;
	ProtocolClient* protocolClient;
	public:
	void receiveBackground();
	ServerReceiver(ProtocolClient* protocol);
	void run() override;
	~ServerReceiver() override;
};

#endif /*__SERVERRECEIVER_H__*/

/*
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

*/