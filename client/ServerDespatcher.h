#ifndef __SERVERDESPATCHER_H__
#define __SERVERDESPATCHER_H__

#include "GameView.h"
#include "thread.h"
#include "BlockingQueue.h"
#include "client_protocol.h"
#include "ClientInput.h"

class ServerDespatcher: public Thread {
	BlockingQueue<ClientInput>* blockingQueue;
	ProtocolClient* protocolClient;
	public:
	ServerDespatcher(ProtocolClient* protocol, BlockingQueue<ClientInput>* blockingQueue);
	void run() override;
	~ServerDespatcher() override;
};

#endif /*__SERVERDESPATCHER_H__*/
