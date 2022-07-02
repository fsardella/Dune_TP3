#ifndef __USERINPUTRECEIVER_H__
#define __USERINPUTRECEIVER_H__

#include <vector>
#include "GameView.h"
#include "thread.h"
#include "BlockingQueue.h"
#include "ClientInput.h"

#define NONE_TYPE -1

class UserInputReceiver: public Thread {
    GameView* gameView;
    BlockingQueue<ClientInput>* blockingQueue;

    int currentMenuImage = NONE_TYPE;
    std::vector<int> touchedUnits;

    int findRow(int y);
    int findCol(int x);
    void handlePosition(int x, int y);
    void handleRightClick(int x, int y);
    bool wasUntouched(int id);

 public:
    UserInputReceiver(GameView* gameViewObj,
                      BlockingQueue<ClientInput>* blockingQueue);
    void run() override;
    ~UserInputReceiver() override;
};

#endif /*__USERINPUTRECEIVER_H__*/
