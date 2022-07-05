#ifndef __SERVER_INPUTGUY_H__
#define __SERVER_INPUTGUY_H__


#include "common_thread.h"
#include <iostream>
#include <string>
#include <map>
#include "server_listener.h"
#include "server_talker.h"
#include "common_blockingqueue.h"

typedef std::map<std::string, Talker*> talkerMap_t;

class InputGuy: public Thread {
    Listener& listeningThread;
    BlockingQueue<Game>& readyGames;
    talkerMap_t& userThreads;
 public:
    InputGuy(Listener& listeningThread, BlockingQueue<Game>& readyGames,
             talkerMap_t& userThreads);
    void run() override;
    ~InputGuy() override;
};

#endif
