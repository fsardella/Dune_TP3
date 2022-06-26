#ifndef __SERVER_INPUTGUY_H__
#define __SERVER_INPUTGUY_H__


#include "common_thread.h"
#include <iostream>
#include <string>
#include "server_listener.h"
#include "common_blockingqueue.h"

// Ta bien, pero post-tpDeTaller no le pongas nombres graciosos a las clases
class InputGuy: public Thread {
    Listener& listeningThread;
    BlockingQueue<Game>& readyGames;
 public:
    InputGuy(Listener& listeningThread, BlockingQueue<Game>& readyGames);
    void run() override;
    ~InputGuy() override;
};

#endif
