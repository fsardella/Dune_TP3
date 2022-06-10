#ifndef DRAWER_H
#define DRAWER_H

#include <atomic>
#include "thread.h"
#include "GameView.h"
#include "Unit.h"

class Drawer : public Thread {
private:
    GameView& gameView;
    void run() override;
    bool running;
public:
    explicit Drawer(GameView& gameView);
    void handle_events(Unit unit);
    void update(float dt);
};


#endif