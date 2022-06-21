#ifndef __SERVER_TIMEWIZARD_H__
#define __SERVER_TIMEWIZARD_H__

#include "common_thread.h"
#include "server_activegame.h"
#include <time.h>

class TimeWizard : public Thread {
    ActiveGame& game;
    
 public:
    TimeWizard(ActiveGame& game);
    void run() override;
	~TimeWizard() override;
};

#endif
