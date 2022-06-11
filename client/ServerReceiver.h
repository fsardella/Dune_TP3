#ifndef __SERVERRECEIVER_H__
#define __SERVERRECEIVER_H__

#include "GameView.h"
#include "Drawer.h"
#include "thread.h"

class ServerReceiver: public Thread {
	Drawer drawer;
	void run() override;
public:
	ServerReceiver(GameView &gameView);
	virtual ~ServerReceiver();
};

#endif