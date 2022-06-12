#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <atomic>
#include "thread.h"
#include "GameView.h"
#include "Unit.h"

class Drawer : public Thread {
    GameView* gameView;
    bool running;
    public:
    explicit Drawer(GameView* gameView);
    void handle_events(Unit unit);
    void update(float dt);
    void run() override;
    ~Drawer() override;
};


#endif