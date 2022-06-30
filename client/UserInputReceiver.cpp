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
#define POSITION_BUILDING 8
#define MOVEMENT 9


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
                if (id != NONE_TYPE) {
                    touchedUnit = id;
                    gameView->touchedUnit(touchedUnit);
                }
                return;
            }
            // FALTA MENSAJE DE DONDE CONSTRUIRLO, CUANDO CRIS NOS MANDE MENSAJE DE CONST TERMINADA.
            // imagen menu con un bool de construcion terminada, imagen menu con sombra de progreso.
            int unitId = gameView->isUnit(posX, posY, false);
            int buildingId = gameView->isBuilding(posX, posY, false);
            if (unitId != NONE_TYPE || buildingId != NONE_TYPE) {
                // op 7
                int attackedType = unitId != NONE_TYPE ? 0 : 1;
                int attackedId = unitId != NONE_TYPE ? unitId : buildingId;
                std::cout << "entro en la opcion 7 que es atacar a otro ";
                std::cout << "ataco a " << attackedType << " con " << touchedUnit << " a " << attackedId << std::endl; 
                ClientInput clientInput(ATTACK, attackedType, touchedUnit, attackedId);
                blockingQueue->push(std::move(clientInput));
                touchedUnit = NONE_TYPE;
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
            std::cout << "entro en la opcion 5 que es crear unidad con el tipo " << unitType << std::endl;
            ClientInput clientInput(CREATE_UNIT, unitType);
            blockingQueue->push(std::move(clientInput));
        }
        currentMenuImage = NONE_TYPE;
        return;
    }
    if (currentMenuImage > 10) {
        // op 6
        int buildingType = currentMenuImage;
        std::cout << "entro en la opcion 6 que es crear un edificio con el tipo " << buildingType << std::endl;
        ClientInput clientInput(CREATE_BUILDING, buildingType);
        blockingQueue->push(std::move(clientInput));
        currentMenuImage = NONE_TYPE;
        return;
    }
}

void UserInputReceiver::handleMovement(int x, int y) {
    int posX = x + gameView->getXOffset() * TILE_SIZE;
    int posY = y + gameView->getYOffset() * TILE_SIZE;
    // int borderX = posX - (posX % TILE_SIZE);
    // int borderY = posY - (posY % TILE_SIZE);
    std::cout << "entre al click derecho\n";
    if (touchedUnit != NONE_TYPE) {
        std::cout << "operacion de movimiento con " << touchedUnit << " y pos " << posX / 4 << "," << posY / 4 << std::endl; 
        int unitId = gameView->isUnit(posX, posY, false);
        int buildingId = gameView->isBuilding(posX, posY, false);
        if (unitId != NONE_TYPE) {
            // quería seguir a una unidad
            std::cout << "me quiero mover hacia la unidad " << unitId << std::endl;
            // ClientInput clientInput(MOVEMENT, touchedUnit, posX / 4, posY / 4);
            // blockingQueue->push(std::move(clientInput));
            // touchedUnit = NONE_TYPE;
            // return;
        }
        if (buildingId != NONE_TYPE) {
            // quería seguir a un edificio
            std::cout << "me quiero mover hacia el edificio " << buildingId << std::endl;
            // ClientInput clientInput(MOVEMENT, touchedUnit, posX / 4, posY / 4);
            // blockingQueue->push(std::move(clientInput));
            // touchedUnit = NONE_TYPE;
            // return;
        }
        ClientInput clientInput(MOVEMENT, touchedUnit, posX / 4, posY / 4);
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