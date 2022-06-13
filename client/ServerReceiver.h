#ifndef __SERVERRECEIVER_H__
#define __SERVERRECEIVER_H__

#include "GameView.h"
#include "thread.h"
#include "client_protocol.h"

class ServerReceiver: public Thread {
	GameView* gameView;
	ProtocolClient* protocolClient;
	public:
	void receiveBackground();
	ServerReceiver(ProtocolClient* protocol, GameView* gameViewObj);
	void run() override;
	~ServerReceiver() override;
};

#endif /*__SERVERRECEIVER_H__*/
