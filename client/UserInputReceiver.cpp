#include "UserInputReceiver.h"
#include <utility>

UserInputReceiver::UserInputReceiver(GameView* gameViewObj, BlockingQueue* blockingQueue): gameView(gameViewObj),
blockingQueue(blockingQueue) {
}

void UserInputReceiver::run() {
    while (gameView->isRunning()) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameView->shutdown();
                break;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                ClientInput clientInput(event.button.x, event.button.y);
                blockingQueue->push(std::move(clientInput));
            }
        }
    }
}

UserInputReceiver::~UserInputReceiver() {
}