#ifndef __SERVER_BROADCASTER_H__
#define __SERVER_BROADCASTER_H__

#include "common_thread.h"

class Broadcaster: public Thread {
    ActiveGame& game;
    talkerMap_t& talkerThreads;
    
};

#endif
