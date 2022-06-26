#ifndef __SERVER_BROADCASTER_H__
#define __SERVER_BROADCASTER_H__

#include "common_thread.h"
#include "server_activegame.h"
#include "common_command.h"
#include "common_blockingqueue.h"

typedef std::map<std::string, BlockingQueue<Command>> queueMap_t;

class Broadcaster: public Thread {
    ActiveGame& game;
    queueMap_t& queues;
    BlockingQueue<Command>& queueToKill;

    int broadcast(/*Command comm*/);
    Command getUnits(std::string recvName); // CAMBIAR PROTOCOLO PARA SACAR
 public:
    Broadcaster(ActiveGame& game, queueMap_t& queues, BlockingQueue<Command>& queueToKill);
    void run() override;
	~Broadcaster() override;
};

#endif
