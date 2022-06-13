#ifndef __USERINPUTRECEIVER_H__
#define __USERINPUTRECEIVER_H__

#include "GameView.h"
#include "thread.h"
#include "BlockingQueue.h"

class UserInputReceiver: public Thread {
	GameView* gameView;
	BlockingQueue* blockingQueue;
	public:
	UserInputReceiver(GameView* gameViewObj, BlockingQueue* blockingQueue);
	void run() override;
	~UserInputReceiver() override;
};

#endif /*__USERINPUTRECEIVER_H__*/
