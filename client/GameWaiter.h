#ifndef __GAME_WAITER_H__
#define __GAME_WAITER_H__

#include <atomic>
#include "thread.h"
#include "client_interface/waitingWindow.h"

class GameWaiter : public Thread {
    WaitingWindow& window;

 public:
    explicit GameWaiter(WaitingWindow& window);
    void run() override;
    ~GameWaiter() override;
};

#endif /*__GAME_WAITER_H__*/
