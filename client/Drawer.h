#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <atomic>
#include "../common/thread.h"
#include "GameView.h"
#include "Unit.h"

class Drawer : public Thread {
    GameView* gameView;
 public:
    explicit Drawer(GameView* gameView);
    void handle_events(Unit unit);
    void update(float dt);
    void run() override;
    ~Drawer() override;
};

#endif /*__DRAWER_H__*/
