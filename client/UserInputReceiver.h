#ifndef __USERINPUTRECEIVER_H__
#define __USERINPUTRECEIVER_H__

#include "GameView.h"
#include "thread.h"
#include "BlockingQueue.h"
#include "ClientInput.h"

#define NONE_TYPE -1

class UserInputReceiver: public Thread {
	GameView* gameView;
	BlockingQueue<ClientInput>* blockingQueue;

	int currentMenuImage = NONE_TYPE;
	int touchedUnit = NONE_TYPE;

	int findRow(int y);
	int findCol(int x);
	void handlePosition(int x, int y);
	void handleMovement(int x, int y);

	public:
	UserInputReceiver(GameView* gameViewObj, BlockingQueue<ClientInput>* blockingQueue);
	void run() override;
	~UserInputReceiver() override;
};

#endif /*__USERINPUTRECEIVER_H__*/
