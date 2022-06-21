#include "UserInputReceiver.h"
#include <utility>

#include <iostream>

#define MENU_OFFSET_X 991
#define MENU_IMAGE_OFFSET_X 993
#define MENU_IMAGE_OFFSET_Y 110
#define SPACING_X 2
#define SPACING_Y 10
#define IMAGE_PIX_WIDTH 100
#define IMAGE_PIX_HEIGHT 75
#define END_ROWS 695
#define END_COLS 1300
#define LAST_ROW 6
#define ERROR -1


UserInputReceiver::UserInputReceiver(GameView* gameViewObj, BlockingQueue<ClientInput>* blockingQueue): gameView(gameViewObj),
blockingQueue(blockingQueue) {
}

int UserInputReceiver::findRow(int y) {
    for (int i = MENU_IMAGE_OFFSET_Y; i < END_ROWS; i += (SPACING_Y + IMAGE_PIX_HEIGHT)) {
        if (i < y && y < (i + IMAGE_PIX_HEIGHT)) {
            if (i == MENU_IMAGE_OFFSET_Y) return 0;
            return (i - MENU_IMAGE_OFFSET_Y) / (SPACING_Y + IMAGE_PIX_HEIGHT);
        }
    }
    return ERROR;
}

int UserInputReceiver::findCol(int x) {
    for (int i = MENU_IMAGE_OFFSET_X; i < END_COLS; i += (SPACING_X + IMAGE_PIX_WIDTH)) {
        if (i < x && x < (i + IMAGE_PIX_WIDTH)) {
            if (i == MENU_IMAGE_OFFSET_X) return 0;
            return (i - MENU_IMAGE_OFFSET_X) / (SPACING_X + IMAGE_PIX_WIDTH);
        }
    }
    return ERROR;
}

void UserInputReceiver::handlePosition(int x, int y) {
    if (0 < x && x < MENU_OFFSET_X) {
        try {
            ClientInput clientInput(x, y);
            blockingQueue->push(std::move(clientInput));
            return;
        } catch(const ClosedQueueException& e) {
            std::cout << "la cola se cerro inesperadamente 2\n";
        }
    }
    int col = findCol(x);
    if (col == ERROR) return;
    int row = findRow(y);
    if (row == ERROR || (row == LAST_ROW && col > 0)) return;

    currentMenuImage = row * 3 + col;
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
                handlePosition(event.button.x, event.button.y);
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