#ifndef __SERVERDESPATCHER_H__
#define __SERVERDESPATCHER_H__

#include "GameView.h"
#include "thread.h"
#include "BlockingQueue.h"
#include "client_protocol.h"

class ServerDespatcher: public Thread {
	BlockingQueue* blockingQueue;
	ProtocolClient* protocolClient;
	public:
	ServerDespatcher(ProtocolClient* protocol, BlockingQueue* blockingQueue);
	void run() override;
	~ServerDespatcher() override;
};

#endif /*__SERVERDESPATCHER_H__*/
