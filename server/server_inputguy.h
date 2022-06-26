#ifndef __SERVER_INPUTGUY_H__
#define __SERVER_INPUTGUY_H__


#include "common_thread.h"
#include <iostream>
#include <string>
#include "server_listener.h"
#include "common_blockingqueue.h"

class InputGuy: public Thread {
    Listener& listeningThread;
    BlockingQueue<Game>& readyGames;
 public:
    InputGuy(Listener& listeningThread, BlockingQueue<Game>& readyGames);
    void run() override;
    ~InputGuy() override;
};

#endif
