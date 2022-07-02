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
#define POSITION_BUILDING 9
#define CHASE 10
#define DESTRUCTION 11



UserInputReceiver::UserInputReceiver(GameView* gameViewObj,
                                     BlockingQueue<ClientInput>* blockingQueue)
: gameView(gameViewObj),
  blockingQueue(blockingQueue)
{}

int UserInputReceiver::findRow(int y) {
    for (int i = MENU_IMAGE_OFFSET_Y; i < END_ROWS; i +=
        (SPACING_Y + IMAGE_PIX_HEIGHT)) {
        if (i < y && y < (i + IMAGE_PIX_HEIGHT)) {
            if (i == MENU_IMAGE_OFFSET_Y) return 0;
            return (i - MENU_IMAGE_OFFSET_Y) / (SPACING_Y + IMAGE_PIX_HEIGHT);
        }
    }
    return ERROR;
}

int UserInputReceiver::findCol(int x) {
    for (int i = MENU_IMAGE_OFFSET_X; i < END_COLS; i +=
        (SPACING_X + IMAGE_PIX_WIDTH)) {
        if (i < x && x < (i + IMAGE_PIX_WIDTH)) {
            if (i == MENU_IMAGE_OFFSET_X) return 0;
            return (i - MENU_IMAGE_OFFSET_X) / (SPACING_X + IMAGE_PIX_WIDTH);
        }
    }
    return ERROR;
}

bool UserInputReceiver::wasUntouched(int id) {
    for (int& i : touchedUnits) {
        if (i == id) return false;
    }
    return true;
}

void UserInputReceiver::handlePosition(int x, int y) {
    int posX = x + gameView->getXOffset() * TILE_SIZE;
    int posY = y + gameView->getYOffset() * TILE_SIZE;
    if (0 < posX && posX < MENU_OFFSET_X) {
        try {
            int id = gameView->isUnit(posX, posY, true);
            if (currentMenuImage == NONE_TYPE && id != NONE_TYPE) {
                if (!wasUntouched(id)) return;
                touchedUnits.push_back(id);
                gameView->touchedUnit(id);
                return;
            }

            int unitId = gameView->isUnit(posX, posY, false);
            int buildingId = gameView->isBuilding(posX, posY, false);

            if (gameView->isBuildingReady(currentMenuImage) &&
                unitId == NONE_TYPE && buildingId == NONE_TYPE) {
                // op 9
                // quiero posicionar un edificio ya listo
                ClientInput clientInput(POSITION_BUILDING, posX / 4, posY / 4);
                blockingQueue->push(std::move(clientInput));
                gameView->setNotReady(currentMenuImage);
                currentMenuImage = NONE_TYPE;
                return;
            }


            if (unitId != NONE_TYPE || buildingId != NONE_TYPE) {
                // op 7
                int attackedType = unitId != NONE_TYPE ? 0 : 1;
                int attackedId = unitId != NONE_TYPE ? unitId : buildingId;
                // quiero atacar a un edificio/unidad
                for (int& touchedId : touchedUnits) {
                    ClientInput clientInput(ATTACK, attackedType,
                                            touchedId, attackedId);
                    blockingQueue->push(std::move(clientInput));
                    gameView->untouchedUnit(touchedId);
                }
                touchedUnits.clear();
                if (unitId != NONE_TYPE) {
                    unitId = NONE_TYPE;
                } else {
                    buildingId = NONE_TYPE;
                }
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

    if (currentMenuImage < 11) {
        // op 5
        int unitType = currentMenuImage;
        if (!gameView->isBlocked(currentMenuImage)) {
            // quiero construir una unidad
            ClientInput clientInput(CREATE_UNIT, unitType);
            blockingQueue->push(std::move(clientInput));
        }
        currentMenuImage = NONE_TYPE;
        return;
    }
    if (currentMenuImage > 10) {
        // op 6
        int buildingType = currentMenuImage;
        if (gameView->isBuildingReady(buildingType)) {
            return;
        }
        if (!gameView->isBuildingUnderConstruction(buildingType)) {
            // quiero construir un edificio
            ClientInput clientInput(CREATE_BUILDING, buildingType);
            blockingQueue->push(std::move(clientInput));
        }
        currentMenuImage = NONE_TYPE;
        return;
    }
}

void UserInputReceiver::handleRightClick(int x, int y) {
    int posX = x + gameView->getXOffset() * TILE_SIZE;
    int posY = y + gameView->getYOffset() * TILE_SIZE;
    // int borderX = posX - (posX % TILE_SIZE);
    // int borderY = posY - (posY % TILE_SIZE);
    if (touchedUnits.size() != 0) {
        int unitId = gameView->isUnit(posX, posY, false);
        int buildingId = gameView->isBuilding(posX, posY, false);
        if (unitId != NONE_TYPE || buildingId != NONE_TYPE) {
            // op 10
            // quiero perseguir a una unidad/edificio
            int chasedId = (unitId == NONE_TYPE) ? buildingId : unitId;
            for (int& id : touchedUnits) {
                ClientInput clientInput(CHASE, id, chasedId);
                blockingQueue->push(std::move(clientInput));
                gameView->untouchedUnit(id);
            }
            touchedUnits.clear();
            return;
        }
        // me quiero mover a una direccion vacia
        // op 8
        for (int& id : touchedUnits) {
            ClientInput clientInput(MOVEMENT, id, posX / 4, posY / 4);
            blockingQueue->push(std::move(clientInput));
            gameView->untouchedUnit(id);
        }
        touchedUnits.clear();
        return;
    }
    // op 11
    // quiero destruir un edificio
    int buildingId = gameView->isBuilding(posX, posY, true);
    if (buildingId != NONE_TYPE) {
        ClientInput clientInput(DESTRUCTION, buildingId);
        blockingQueue->push(std::move(clientInput));
    }
}

void UserInputReceiver::run() {
    while (gameView->isRunning()) {
        SDL_Event event;
        bool selection;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameView->shutdown();
                blockingQueue->close();
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                    event.button.button == SDL_BUTTON_LEFT) {
                selection = true;
                handlePosition(event.button.x, event.button.y);
            } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                    event.button.button == SDL_BUTTON_RIGHT) {
                handleRightClick(event.button.x, event.button.y);
            } else if (event.type == SDL_MOUSEMOTION && selection) {
                handlePosition(event.button.x, event.button.y);
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                selection = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
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
