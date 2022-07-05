#ifndef __SERVERDISPATCHER_H__
#define __SERVERDISPATCHER_H__

#include "GameView.h"
#include "../common/thread.h"
#include "BlockingQueue.h"
#include "client_protocol.h"
#include "ClientInput.h"

class ServerDispatcher: public Thread {
    ProtocolClient* protocolClient;
    BlockingQueue<ClientInput>* blockingQueue;

 public:
    ServerDispatcher(ProtocolClient* protocol,
                     BlockingQueue<ClientInput>* blockingQueue);
    void run() override;
    ~ServerDispatcher() override;
};

#endif /*__SERVERDISPATCHER_H__*/
