#ifndef __SERVER_SENDER_H__
#define __SERVER_SENDER_H__


#include "common_thread.h"
#include "common_blockingqueue.h"
#include "server_command.h"
#include "server_protocol.h"

class Sender : public Thread {
    BlockingQueue<Command>& queue;
    ProtocolServer& protocol;
 public:
    Sender(BlockingQueue<Command>& queue, ProtocolServer& protocol);
    void run() override;
	~Sender() override;
};









#endif
