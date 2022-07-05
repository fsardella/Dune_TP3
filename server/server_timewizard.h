#ifndef __SERVER_TIMEWIZARD_H__
#define __SERVER_TIMEWIZARD_H__

#include "common_thread.h"
#include "server_activegame.h"
#include "server_config.h"
#include <time.h>

class TimeWizard : public Thread {
    int delta;
    ActiveGame& game;
    
 public:
    TimeWizard(ActiveGame& game, Config* c);
    void run() override;
	~TimeWizard() override;
};

#endif
