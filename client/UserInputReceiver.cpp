#include "UserInputReceiver.h"
#include <utility>

UserInputReceiver::UserInputReceiver(GameView* gameViewObj, BlockingQueue<ClientInput>* blockingQueue): gameView(gameViewObj),
blockingQueue(blockingQueue) {
}

void UserInputReceiver::run() {
    while (gameView->isRunning()) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameView->shutdown();
                blockingQueue->close();
                break;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                ClientInput clientInput(event.button.x, event.button.y); // tambien tendría la unidad del otro menu
                blockingQueue->push(std::move(clientInput));
            }
            else if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP: gameView->moveUpwards(); break;
                    case SDLK_DOWN: gameView->moveDownwards(); break;
                    case SDLK_LEFT: gameView->moveLeft(); break;
                    case SDLK_RIGHT: gameView->moveRight(); break;
                }
            }
        }
    }
}

UserInputReceiver::~UserInputReceiver() {
}