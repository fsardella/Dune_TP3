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
	void run() override;
	void receiveBackground();

public:
	ServerReceiver(ProtocolClient* protocol);
	virtual ~ServerReceiver();
};

#endif