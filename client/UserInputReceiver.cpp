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

#define TILE_SIZE 32

#define CREATE_UNIT 5
#define CREATE_BUILDING 6
#define ATTACK 7
#define MOVEMENT 8


UserInputReceiver::UserInputReceiver(GameView* gameViewObj,
                                     BlockingQueue<ClientInput>* blockingQueue)
: gameView(gameViewObj),
  blockingQueue(blockingQueue) 
{}

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
    int posX = x + gameView->getXOffset() * TILE_SIZE;
    int posY = y + gameView->getYOffset() * TILE_SIZE;
    if (0 < posX && posX < MENU_OFFSET_X) {
        try {
            if (currentMenuImage == NONE_TYPE && touchedUnit == NONE_TYPE) {
                int id = gameView->isUnit(posX, posY, true);
                if (id != NONE_TYPE) touchedUnit = id;
                return;
            }
            if (currentMenuImage < 11) {
                // op 5
                int unitType = currentMenuImage;
                if (!gameView->isBlocked(currentMenuImage)) {
                    ClientInput clientInput(CREATE_UNIT, unitType);
                    blockingQueue->push(std::move(clientInput));
                }
                currentMenuImage = NONE_TYPE;
                return;
            }
            int borderX = posX - (posX % TILE_SIZE);
            int borderY = posY - (posY % TILE_SIZE);
            if (currentMenuImage > 10) {
                // op 6
                int buildingType = currentMenuImage;
                ClientInput clientInput(CREATE_BUILDING, buildingType, borderX / 4, borderY / 4);
                blockingQueue->push(std::move(clientInput));
                currentMenuImage = NONE_TYPE;
                return;
            }
            int unitId = gameView->isUnit(borderX,borderY, false); // puede devolver -1 si no
            int buildingId = gameView->isBuilding(borderX, borderY, false); // puede devolver -1 si no
            if (unitId != NONE_TYPE || buildingId != NONE_TYPE) {
                // op 7
                int attackedType = unitId != NONE_TYPE ? 0 : 1;
                ClientInput clientInput(ATTACK, attackedType, touchedUnit, unitId);
                blockingQueue->push(std::move(clientInput));
                touchedUnit = NONE_TYPE;
                return;
            }
        } catch(const ClosedQueueException& e) {
            return;
        }
    }
    int col = findCol(x);
    if (col == ERROR) return;
    int row = findRow(y);
    if (row == ERROR || (row == LAST_ROW && col > 0)) return;

    currentMenuImage = row * 3 + col;
}

void UserInputReceiver::handleMovement(int x, int y) {
    int posX = x + gameView->getXOffset() * TILE_SIZE;
    int posY = y + gameView->getYOffset() * TILE_SIZE;
    int borderX = posX - (posX % TILE_SIZE);
    int borderY = posY - (posY % TILE_SIZE);
    if (touchedUnit) {
        ClientInput clientInput(MOVEMENT, touchedUnit, borderX / 4, borderY / 4);
        blockingQueue->push(std::move(clientInput));
        touchedUnit = NONE_TYPE;
        return;
    }
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
            else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                handlePosition(event.button.x, event.button.y);
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
                handleMovement(event.button.x, event.button.y);
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