#include "MenuImage.h"
#include "Camera.h"
#include <utility>

#include <iostream>

#define BARRACK 18
#define LIGHT_FACTORY 12
#define HEAVY_FACTORY 13
#define PALACE 14
#define CONSTRUCTIONS_OFFSET 11
#define UNIT_LIMIT 10
#define COMPLETE 100
#define PROGRESS_COMPLETED 100

/*
Pre-Condiciones: Constructor del MenuImage.
Post-Condiciones: -
*/

MenuImage::MenuImage(SdlTexture* texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY,
           int type,
           std::vector<int>& houses)
: Renderizable(texture, sizeW, sizeH, posX, posY),
  type(type),
  blocked(false),
  barracks(0),
  palaces(0),
  heavyFactorys(0),
  lightFactorys(0),
  isUnderConstruction(false),
  progress(0),
  isReady(false),
  isTouched(false),
  houses(houses) {
    if (type < CONSTRUCTIONS_OFFSET) blocked = true;
    rescaling = 1;
}

void MenuImage::render(Camera &camera) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSightForMenu(texture, src, posX, posY);
    if (blocked && type < CONSTRUCTIONS_OFFSET) {
        camera.renderBlockingFigure(posX, posY);
    }
    if (blocked && type > UNIT_LIMIT) {
        Area shadowScrBlocked(0, 0, sizeW, sizeH);
        camera.renderShadowForMenu(shadowScrBlocked, posX, posY, 0);
    }
    if (isUnderConstruction) {
        Area shadowScr(0, 0, sizeW, sizeH - (sizeH * (static_cast<float>
                       (progress) / static_cast<float>(100))));
        camera.renderShadowForMenu(shadowScr, posX, posY, progress);
    }
    if (isReady) {
        camera.renderReadyFigure(posX, posY);
    }
    if (isTouched) {
        camera.renderMenuFrame(posX, posY);
    }
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición x.
*/

int MenuImage::getX() {
    return posX;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve la posición y.
*/

int MenuImage::getY() {
    return posY;
}

/*
Pre-Condiciones: Setea al atributo isTouched con el booleano recibido.
Post-Condiciones: -
*/

void MenuImage::setTouched(bool state) {
    isTouched = state;
}


/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si esta bloqueada esa imagen o false si no.
*/

bool MenuImage::isBlocked() {
    return blocked;
}

/*
Pre-Condiciones: Se construye un edificio. 
Post-Condiciones: Chequea si una imagen de una unidad del menu 
puede ser desbloqueada según el tipo de edificio que se le pasa por 
parámetro. Devuelve true si se puede desbloquear o false si no. 
*/

bool MenuImage::checkUnblockPosibility(int buildingType) {
    if (type < 2 && lightFactorys != 0) return true;
    if (type >= 2 && type < 4 && heavyFactorys != 0) return true;
    if (type > 3 && type < 7 && heavyFactorys != 0 && palaces != 0)
        return true;
    if (type > 3 && type < 7 && palaces != 0 && heavyFactorys != 0)
        return true;
    if (type > 6 && type < 9 && barracks != 0) return true;
    if (type > 8 && type < 11 && barracks != 0 && palaces != 0)
        return true;
    if (type > 8 && type < 11 && palaces != 0 && barracks != 0)
        return true;
    return false;
}

/*
Pre-Condiciones: Se construye un edificio. 
Post-Condiciones: Actualiza la cantidad de edificios según su tipo.
*/

void MenuImage::updateBuildings(int buildingType) {
    if (buildingType == BARRACK) barracks += 1;
    if (buildingType == HEAVY_FACTORY) heavyFactorys += 1;
    if (buildingType == PALACE) palaces += 1;
    if (buildingType == LIGHT_FACTORY) lightFactorys += 1;
}

/*
Pre-Condiciones: Chequea si la casa del jugador coincide 
con alguna de las posibles casas de una determinada unidad
para poder desbloquear a la misma.
Post-Condiciones: - 
*/

bool MenuImage::checkHouse(int house) {
    for (int& posibleHouse : houses) {
        if (posibleHouse == house) return true;
    }
    return false;
}

/*
Pre-Condiciones: Se crea un edificio.
Post-Condiciones: Se chequea el desbloqueo de la unidad según la casa
que eligió el jugador y el tipo de edificio creado. 
*/

void MenuImage::updateUnblocking(int buildingType, int house) {
    if (!checkHouse(house)) {
        return;
    }
    updateBuildings(buildingType);
    if (checkUnblockPosibility(buildingType)) {
        blocked = false;
    }
}

/*
Pre-Condiciones: Se destruye un edificio.
Post-Condiciones: Se chequea el bloqueo de la unidad según 
el tipo de edificio destruido. 
*/

void MenuImage::updateBlocking(int buildingType, int house) {
    if (!checkHouse(house)) return;
    if (buildingType == BARRACK) barracks -= 1;
    if (buildingType == HEAVY_FACTORY) heavyFactorys -= 1;
    if (buildingType == PALACE) palaces -= 1;
    if (buildingType == LIGHT_FACTORY) lightFactorys -= 1;
    if (type < CONSTRUCTIONS_OFFSET) {
        if (isUnderConstruction && !checkUnblockPosibility(buildingType)) {
            isUnderConstruction = false;
        }
        blocked = !checkUnblockPosibility(buildingType);
    }
}

void MenuImage::block() {
    blocked = true;
}

void MenuImage::unblock() {
    blocked = false;
}

/*
Pre-Condiciones: Se actualiza el progreso de construcción
o entrenamiento de edificios o unidades.
Post-Condiciones: -
*/

void MenuImage::updateProgress(int progress) {
    if (blocked) return;
    if (!isUnderConstruction) {
        isUnderConstruction = true;
    }
    this->progress = progress;
    if (progress == COMPLETE) {
        if (type > UNIT_LIMIT) isReady = true;
        isUnderConstruction = false;
    }
}

/*
Pre-Condiciones: Determina si un edificio o una unidad están
en construcción o entrenamiento.
Post-Condiciones: Devuelve true si lo están o false si no. 
*/

bool MenuImage::isCurrentlyUnderConstruction() {
    return isUnderConstruction;
}

/*
Pre-Condiciones: Determina si un edificio ya fue construido
y esta listo para ser posicionado.
Post-Condiciones: Devuelve true si lo esta o false si no. 
*/

bool MenuImage::isBuildingReady() {
    return isReady;
}

/*
Pre-Condiciones: Setea que un edificio aún no esta construido.
Post-Condiciones: -
*/

void MenuImage::setNotReady() {
    isReady = false;
}

/*
Pre-Condiciones: Constructor del MenuImage.
Post-Condiciones: -
*/

MenuImage::MenuImage(MenuImage &&other)
: Renderizable(std::move(other)),
  type(other.type),
  rescaling(other.rescaling),
  blocked(other.blocked),
  barracks(other.barracks),
  palaces(other.palaces),
  heavyFactorys(other.heavyFactorys),
  lightFactorys(other.lightFactorys),
  isUnderConstruction(other.isUnderConstruction),
  progress(other.progress),
  isReady(other.isReady),
  isTouched(other.isTouched),
  houses(other.houses) {
}

/*
Pre-Condiciones: Destructor del MenuImage.
Post-Condiciones: -
*/

MenuImage::~MenuImage() {
}
