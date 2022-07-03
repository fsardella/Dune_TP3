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

#define CONSTRUCTION_OFFSET 11
#define UNIT_LIMIT 10

/*
Pre-Condiciones: Constructor de UserInputReceiver.
Post-Condiciones: -
*/

UserInputReceiver::UserInputReceiver(GameView* gameViewObj,
                                     BlockingQueue<ClientInput>* blockingQueue)
: gameView(gameViewObj),
  blockingQueue(blockingQueue)
{}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la fila donde toco el jugador o -1 en caso de error.
*/

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

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la columna donde toco el jugador o -1 
en caso de error.
*/

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

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true en caso de que las unidades se dejan de
visualizar como tocadas o false si no.
*/
bool UserInputReceiver::wasUntouched(int id) {
    for (int& i : touchedUnits) {
        if (i == id) return false;
    }
    return true;
}

/*
Pre-Condiciones: Maneja las opciones cuando se hace click izquierdo:
si se clickeo sobre una unidad o edificio (para que sean atacados), 
sobre el mapa (para posicionar un edificio) o sobre el menu (para 
construir un edificio o entrenar una unidad).
Post-Condiciones: -
*/

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
                std::cout << "op 9\n";
                // quiero posicionar un edificio ya listo
                std::cout << "estoy enviando " << posX << " y " << posY << std::endl;
                ClientInput clientInput(POSITION_BUILDING, posX / 4, posY / 4);
                blockingQueue->push(std::move(clientInput));
                gameView->setNotReady(currentMenuImage);
                currentMenuImage = NONE_TYPE;
                return;
            }


            if (unitId != NONE_TYPE || buildingId != NONE_TYPE) {
                // op 7
                std::cout << "op 7\n";
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

    if (currentMenuImage < CONSTRUCTION_OFFSET) {
        // op 5
        std::cout << "op 5\n";
        int unitType = currentMenuImage;
        if (gameView->isUnderConstruction(unitType)) {
            currentMenuImage = NONE_TYPE;
            return;
        }
        if (!gameView->isBlocked(currentMenuImage)) {
            // quiero construir una unidad
            ClientInput clientInput(CREATE_UNIT, unitType);
            blockingQueue->push(std::move(clientInput));
        }
        currentMenuImage = NONE_TYPE;
        return;
    }
    if (currentMenuImage > UNIT_LIMIT) {
        // op 6
        std::cout << "op 6\n";
        int buildingType = currentMenuImage;
        if (gameView->isBuildingReady(buildingType)) {
            return;
        }
        if (!gameView->isUnderConstruction(buildingType)) {
            // quiero construir un edificio
            ClientInput clientInput(CREATE_BUILDING, buildingType);
            blockingQueue->push(std::move(clientInput));
        }
        currentMenuImage = NONE_TYPE;
        return;
    }
}

/*
Pre-Condiciones: Maneja las opciones cuando se hace click derecho:
si se clickeo sobre una unidad (para movimiento o para atacar) o sobre 
un edificio (para que su dueño lo destruya).
Post-Condiciones: -
*/

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
            std::cout << "op 10\n";
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
        std::cout << "op 8\n";
        for (int& id : touchedUnits) {
            ClientInput clientInput(MOVEMENT, id, posX / 4, posY / 4);
            blockingQueue->push(std::move(clientInput));
            gameView->untouchedUnit(id);
        }
        touchedUnits.clear();
        return;
    }
    // op 11
    std::cout << "op 11\n";
    // quiero destruir un edificio
    int buildingId = gameView->isBuilding(posX, posY, true);
    if (buildingId != NONE_TYPE) {
        ClientInput clientInput(DESTRUCTION, buildingId);
        blockingQueue->push(std::move(clientInput));
    }
}

/*
Pre-Condiciones: Se lanza el UserInputReceiver.
Post-Condiciones: -
*/

void UserInputReceiver::run() {
    bool close = false;
    while (gameView->isRunning()) {
        SDL_Event event;
        bool selection;
        while (SDL_PollEvent(&event)) {
            if (!gameView->isRunning()) {
                close = true;
                blockingQueue->close();
                break;
            } else if (event.type == SDL_QUIT && gameView->isRunning()) {
                close = true;
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
    if (!close) {
        blockingQueue->close();
    }
}

/*
Pre-Condiciones: Destructor de UserInputReceiver.
Post-Condiciones: -
*/

UserInputReceiver::~UserInputReceiver() {
}
