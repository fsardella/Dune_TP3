#include "MapView.h"
#include "Camera.h"
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <utility>

#include <iostream>

// #define CONSTRUCTION_OFFSET 11
// antes esto estaba en el at de buildConstruction va?
#define UNIT_PIX_SIZE 12
#define BARRACK 18
#define HEAVY_FACTORY 13
#define SILO 16
#define PROGRESS_COMPLETED 100
#define HARKONNEN_SOUND_OFFSET 14
#define ATREIDES_SOUND_OFFSET 19
#define ORDOS_SOUND_OFFSET 24
#define UNIT_CREATED 4
#define UNIT_ATTACKED 29
#define BUILDING_CREATED 2
#define HOUSE_HARKONNEN 0
#define HOUSE_ATREIDES 1
#define HOUSE_ORDOS 2
#define CONSTRUCTION_YARD_ID 11
#define CONSTRUCTION_YARD_ATTACKED 3
#define WITHOUT_LIFE 0
#define EXPLOSION 11
#define MISIL_SOUND 13
#define GUN_SOUND 12
#define WORM_WIDTH 62
#define WORM_HEIGHT 36
#define INITIAL_MONEY 1000
#define INITIAL_ENERGY 100
#define SPICE_OFFSET 22
#define SIZE_FONT 22
#define BARRACK_OFFSET 18
#define FONT_PATH "/usr/share/fonts/type1/urw-base35/URWBookman-Demi.t1"
#define SPRITES_PATH "../client/sprites.yaml"
#define TILES_PATH "../client/tiles.yaml"
#define MENU_PATH "../client/menu.yaml"
#define IDENT_PATH "../client/ident.yaml"
#define LIFE_PATH "../client/animations/vida"
#define ARMAMENT_PATH "../client/armament.yaml"
#define WORM_PATH "../client/animations/Worm"


/*
Pre-Condiciones: Constructor del MapView.
Post-Condiciones: -
*/

MapView::MapView(SdlWindow& window, int houseNumberClient)
: window(window),
  houseNumberClient(houseNumberClient),
  columns(0),
  rows(0),
  actualMoney(0),
  actualEnergy(0),
  worm(std::move(wormEmptyTexturesInitializer()),
       WORM_WIDTH, WORM_HEIGHT, 0, 0) {
    this->loadFontTitles();
    this->loadTileTranslator();
    this->loadMenuTranslator();
    this->loadSpritesTranslator();
    this->loadLifeTranslator();
    this->loadAttackTranslator();
    this->loadIdentifierTranslator();
    this->loadWormTranslator();
    this->createMenu();
    this->setEnergy(INITIAL_ENERGY);
    this->setMoney(INITIAL_MONEY);
}

/*
Pre-Condiciones: Se carga la fuente a utilizar en el menu del mapa.
Post-Condiciones: -
*/

void MapView::loadFontTitles() {
    TTF_Init();
    font = TTF_OpenFont(FONT_PATH, SIZE_FONT);
}

/*
Pre-Condiciones: Se carga el traductor de sprites.
Post-Condiciones: -
*/

void MapView::loadSpritesTranslator() {
    YAML::Node node = YAML::LoadFile(SPRITES_PATH);
    int amount = node["amount"].as<int>();
    for (int i = 0; i < amount; i++) {
        std::map<std::tuple<int, int>, SdlTexture> animations;
        std::string animationAmountText(std::to_string(i) +
                                        "_animationAmount");
        int animationAmount = node[animationAmountText].as<int>();
        for (int j = 0; j < animationAmount; j++) {
            std::string animationIndex(std::to_string(i) + "_" +
                                       std::to_string(j));
            std::vector<std::string> spritesInfo = node[animationIndex].as<
                                                   std::vector<std::string>>();
            for (size_t k = 0; k < spritesInfo.size(); k ++) {
                std::string path = spritesInfo[k];
                animations.emplace(std::piecewise_construct,
                                  std::forward_as_tuple(std::make_tuple(j, k)),
                                  std::forward_as_tuple(path, &window,
                                                        0, 0, 0));
            }
        }
        animationsRepository.insert({i, std::move(animations)});
    }
}

/*
Pre-Condiciones: Se carga el traductor de tiles.
Post-Condiciones: -
*/

void MapView::loadTileTranslator() {
    YAML::Node node = YAML::LoadFile(TILES_PATH);
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> tileInfo = node[i].as<std::vector<
                                                    std::string>>();
        tileInfoTranslator[i] = tileInfo;

        tileTextureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(i),
                          std::forward_as_tuple(tileInfo[1], &window));
    }
}

/*
Pre-Condiciones: Se carga el traductor del menu.
Post-Condiciones: -
*/

void MapView::loadMenuTranslator() {
    YAML::Node node = YAML::LoadFile(MENU_PATH);
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> menuImgInfo = node[i].as<std::vector<
                                                          std::string>>();
        std::string key(std::to_string(i) + "_houses");
        std::vector<int> menuImgHouses = node[key].as<std::vector<int>>();
        menuInfoHouses.insert(std::pair{i, std::move(menuImgHouses)});
        menuTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(menuImgInfo[1],
                                      &window));
    }
}

/*
Pre-Condiciones: Se carga el traductor de identificadores de jugadores.
Post-Condiciones: -
*/

void MapView::loadIdentifierTranslator() {
    YAML::Node node = YAML::LoadFile(IDENT_PATH);
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        std::vector<std::string> identifierMgsInfo = node[i].as<std::vector<
                                                               std::string>>();
        identifierTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(
                                      identifierMgsInfo[0],
                                      &window));
    }
}

/*
Pre-Condiciones: Se carga el traductor de vidas de las unidades y
construcciones.
Post-Condiciones: -
*/

void MapView::loadLifeTranslator() {
    for (int i = 1; i <= 4; i ++) {
        std::string path(LIFE_PATH + std::to_string(i) + ".bmp");
        lifeTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(path,
                                      &window));
    }
}

/*
Pre-Condiciones: Se carga el traductor de armamentos para unidades.
Post-Condiciones: -
*/

void MapView::loadAttackTranslator() {
    YAML::Node node = YAML::LoadFile(ARMAMENT_PATH);
    int amount = node["amount"].as<int>();
    for (int i = 0; i <= amount; i++) {
        if (i == 3) continue;
        std::vector<std::string> attackInfo = node[i].as<std::vector<
                                                         std::string>>();
        for (size_t j = 0; j < attackInfo.size(); j++) {
                attackTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(
                                      std::make_tuple(i, j)),
                                      std::forward_as_tuple(attackInfo[j],
                                                            &window));
        }
    }
}

/*
Pre-Condiciones: Se carga el traductor de las animaciones para el gusano
de arena.
Post-Condiciones: -
*/

void MapView::loadWormTranslator() {
    for (int i = 0; i < 5; i ++) {
        std::string path(WORM_PATH + std::to_string(i + 1) + ".bmp");
        wormTextureTranslator.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(i),
                                      std::forward_as_tuple(path, &window,
                                                            0, 0, 0));
    }
    this->wormTexturesInitializer();
}

/*
Pre-Condiciones: Se crea el menu del juego con sus construcciones y unidades
disponibles, dinero y energía del jugador.
Post-Condiciones: -
*/

void MapView::createMenu() {
    for (size_t i = 0; i <= 18; i += 3) {
        for (size_t j = 0; j < 3; j++) {
            size_t row = i / 3;
            if (i == 18 && j == 0) {
                auto image = menuTextureTranslator.find(houseNumberClient +
                                                        BARRACK_OFFSET);
                menuImages.emplace_back(&image->second, IMAGE_PIX_WIDTH,
                                        IMAGE_PIX_HEIGHT, j, row, BARRACK_OFFSET,
                                        menuInfoHouses.at(houseNumberClient
                                        + BARRACK_OFFSET));
                continue;
            }
            if (i == 18 && j > 0) continue;
            if (i == 0) row = i;
            auto image = menuTextureTranslator.find(i + j);
            menuImages.emplace_back(&image->second, IMAGE_PIX_WIDTH,
                                    IMAGE_PIX_HEIGHT, j, row, i + j,
                                    menuInfoHouses.at(i + j));
        }
    }
}

/*
Pre-Condiciones: Se inicializan las texturas del gusano de arena a
partir de su traductor.
Post-Condiciones: -
*/

void MapView::wormTexturesInitializer() {
    std::vector<SdlTexture*> textures;
    for (int i = 0; i < 5; i ++) {
        textures.push_back(&(wormTextureTranslator.at(i)));
    }
    worm.setTextures(std::move(textures));
}

std::vector<SdlTexture*> MapView::wormEmptyTexturesInitializer() {
    std::vector<SdlTexture*> textures;
    return textures;
}

/*
Pre-Condiciones: Se inicializan las texturas del mapa a
partir de su traductor.
Post-Condiciones: -
*/

void MapView::createMap(int height, int width, std::vector<std::vector<
                        uint8_t>> map) {
    columns = width;
    rows = height;
    for (size_t i = 0; i < rows; i ++) {
        for (size_t j = 0; j < columns; j++) {
            std::vector<std::string> tileInfo = tileInfoTranslator[map[i][j]];
            auto& backgroundTexture = tileTextureTranslator.at(map[i][j]);
            backgroundTiles.emplace_back(&backgroundTexture, TILE_PIX_SIZE,
                                         TILE_PIX_SIZE, j, i);
        }
    }
}

/*
Pre-Condiciones: Se crea una unidad con: animaciones, sprites de
ataque, identificador, texturas de vida, de que jugador es. 
Post-Condiciones: -
*/

void MapView::createUnit(int x, int y, int unitId, int unitType, int playerId,
                         int animationId, bool propiety) {
    float posX = static_cast<float>(x) / static_cast<float>(TILE_PIX_SIZE);
    float posY = static_cast<float>(y) / static_cast<float>(TILE_PIX_SIZE);

    if (unitTiles.find(unitId) != unitTiles.end() &&
        unitTiles.at(unitId).getAnimationId() ==
        unitTiles.at(unitId).findAnimationId(animationId) &&
        unitTiles.at(unitId).getX() == posX &&
        unitTiles.at(unitId).getY() == posY) {
            return;
    }
    if (unitTiles.find(unitId) != unitTiles.end()) {
        if (unitTiles.at(unitId).getAnimationId() !=
        unitTiles.at(unitId).findAnimationId(animationId)) {
            unitTiles.at(unitId).setAnimationId(animationId);
        }
        if (unitTiles.at(unitId).getX() != posX ||
            unitTiles.at(unitId).getY() != posY) {
            unitTiles.at(unitId).setNewPosition(posX, posY);
        }
        return;
    }

    std::vector<SdlTexture*> attackSprites;
    for (int i = 0; i < 3; i ++) {
        attackSprites.push_back(&(attackTextureTranslator.at(std::make_tuple(
                                                             unitType, i))));
    }

    unitTiles.emplace(std::piecewise_construct,
                       std::forward_as_tuple(unitId),
                       std::forward_as_tuple(animationsRepository.at(unitType),
                                             lifeTextureTranslator,
                                             std::move(attackSprites),
                                             &(identifierTranslator.at(
                                               playerId)),
                                             UNIT_PIX_SIZE, UNIT_PIX_SIZE,
                                             posX, posY, propiety, unitType,
                                             playerId, animationId));
}

/*
Pre-Condiciones: Se actualiza el bloqueo de unidades para mostrarse en el menu.
Post-Condiciones: -
*/

void MapView::updateBlockedUnits(int constType, int house) {
    for (MenuImage &image : menuImages) {
        image.updateUnblocking(constType, house);
    }
}

/*
Pre-Condiciones: Se actualiza el desbloqueo de unidades para 
mostrarse en el menu.
Post-Condiciones: -
*/

void MapView::updateUnblockedUnits(int constType) {
    for (MenuImage &image : menuImages) {
        image.updateBlocking(constType);
    }
}

/*
Pre-Condiciones: Se setea el tamaño del edificio a partir de su tipo.
Post-Condiciones: -
*/

void MapView::getBuildingDimensions(int constType, int* width, int* height) {
    if (constType == HEAVY_FACTORY) {
        *width = 4 * TILE_PIX_SIZE;
        *height = 4 * TILE_PIX_SIZE;
        return;
    }
    if (constType == SILO) {
        *width = TILE_PIX_SIZE;
        *height = TILE_PIX_SIZE;
        return;
    }
    if (constType == BARRACK) {
        *width = 2 * TILE_PIX_SIZE;
        *height = 3 * TILE_PIX_SIZE;
        return;
    }
    *width = 3 * TILE_PIX_SIZE;
    *height = 3 * TILE_PIX_SIZE;
}

/*
Pre-Condiciones: Se crea un edificio con: su tipo, dimensiones, animaciones, 
identificador, texturas de vida, casa, de que jugador es.
En caso de que una construccion desbloquee una unidad, se actualizará ese
desbloqueo. 
Post-Condiciones: -
*/

void MapView::createConstruction(int x, int y, int playerId,
                                 int constructionId, int constType,
                                 bool propiety, int house) {
    float posX = static_cast<float>(x) / static_cast<float>(TILE_PIX_SIZE);
    float posY = static_cast<float>(y) / static_cast<float>(TILE_PIX_SIZE);

    if (constType == BARRACK) {
        constType += house;
    }
    int width, height;
    getBuildingDimensions(constType, &width, &height);

    std::cout << "const Type " << constType << std::endl;
    std::cout << "player Id " << playerId << std::endl;

    constructionTiles.emplace(std::piecewise_construct,
                    std::forward_as_tuple(constructionId),
                    std::forward_as_tuple(animationsRepository.at(constType),
                                          lifeTextureTranslator,
                                          &(identifierTranslator.at(playerId)),
                                          width, height, posX, posY,
                                          constType, playerId, propiety));
    updateBlockedUnits(constType, house);
}

/*
Pre-Condiciones: Se actualiza el progreso de creación de un edificio
o de una unidad.
Post-Condiciones: -
*/

void MapView::updateProgress(int menuId, int progress) {
    int offset = getSoundOffset();

    if (menuId > 10 && progress == PROGRESS_COMPLETED &&
        !menuImages.at(menuId).isBuildingReady()) {
        window.playSound(offset + BUILDING_CREATED, VOLUME);
    }

    if (progress == PROGRESS_COMPLETED && menuId < 11) {
        window.playSound(offset + UNIT_CREATED, VOLUME);
    }
    menuImages.at(menuId).updateProgress(progress);
}

/*
Pre-Condiciones: Determina que el jugador toco a una unidad. 
Post-Condiciones: -
*/

void MapView::touchedUnit(int unitId) {
    window.playSound(unitTiles.at(unitId).getUnitType(), VOLUME);
    unitTiles.at(unitId).setIsTouched(true);
}

/*
Pre-Condiciones: La unidad tocada vuelve a su estado actual:
no tocada.
Post-Condiciones: -
*/

void MapView::untouchedUnit(int unitId) {
    unitTiles.at(unitId).setIsTouched(false);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve un offset para determinar el sonido según
la casa elegida por el jugador. 
*/

int MapView::getSoundOffset() {
    if (houseNumberClient == HOUSE_HARKONNEN) {
        return HARKONNEN_SOUND_OFFSET;
    } else if (houseNumberClient == HOUSE_ATREIDES) {
        return ATREIDES_SOUND_OFFSET;
    } else {
        return ORDOS_SOUND_OFFSET;
    }
}

/*
Pre-Condiciones: Establece como debería reaccionar la unidad atacada.
Post-Condiciones: -
*/

void MapView::attackUnitReaction(int attackedId, int currentLife, int totalLife) {
    unitTiles.at(attackedId).updateLife(currentLife, totalLife);
    if ((currentLife == WITHOUT_LIFE) &&
        (unitTiles.at(attackedId).getUnitType() > 6
        && unitTiles.at(attackedId).getUnitType() < 11)) {
        window.playSound(EXPLOSION, VOLUME);
    }
}

/*
Pre-Condiciones: Establece como debería reaccionar el edificio atacado.
Post-Condiciones: -
*/

void MapView::attackBuildingReaction(int attackedId, int currentLife, int totalLife) {
    constructionTiles.at(attackedId).updateLife(currentLife, totalLife);
    if (currentLife == WITHOUT_LIFE) {
        window.playSound(EXPLOSION, VOLUME);
    }
}

/*
Pre-Condiciones: Maneja el ataque a una unidad. 
Post-Condiciones: -
*/

void MapView::attackUnit(int attackerId, int attackedId, int currentLife,
                         int totalLife) {
    if (attackerId == -1) {
        attackUnitReaction(attackedId, currentLife, totalLife);
        return;
    }
    if (unitTiles.at(attackedId).getPropiety()) {
        window.playSound(UNIT_ATTACKED, VOLUME);
    }

    unitTiles.at(attackerId).startAttacking();

    if ((unitTiles.at(attackerId).getUnitType() == 4) ||
        ((unitTiles.at(attackerId).getUnitType() > 7) &&
        (unitTiles.at(attackerId).getUnitType() < 11))) {
         window.playSound(MISIL_SOUND, VOLUME);
    } else if ((unitTiles.at(attackerId).getUnitType() == 0 ||
        (unitTiles.at(attackerId).getUnitType() == 7))) {
        window.playSound(GUN_SOUND, VOLUME);
    }
    attackUnitReaction(attackedId, currentLife, totalLife);
}

/*
Pre-Condiciones: Maneja el ataque a un edificio. 
Post-Condiciones: -
*/

void MapView::attackBuilding(int attackerId, int attackedId, int currentLife,
                             int totalLife) {
    if (attackerId == -1) {
        attackBuildingReaction(attackedId, currentLife, totalLife);
        return;
    }
    if ((constructionTiles.at(attackedId).getConstType() ==
        CONSTRUCTION_YARD_ID) &&
        (constructionTiles.at(attackedId).getPropiety())) {
        int offset = getSoundOffset();
        window.playSound(offset + CONSTRUCTION_YARD_ATTACKED, VOLUME);
    }
    unitTiles.at(attackerId).startAttacking();

    if ((unitTiles.at(attackerId).getUnitType() == 4) ||
        ((unitTiles.at(attackerId).getUnitType() > 7) &&
        (unitTiles.at(attackerId).getUnitType() < 11))) {
        window.playSound(MISIL_SOUND, VOLUME);
    } else if ((unitTiles.at(attackerId).getUnitType() == 0 ||
        (unitTiles.at(attackerId).getUnitType() == 7))) {
        window.playSound(GUN_SOUND, VOLUME);
    }

    if (currentLife == 0 && constructionTiles.at(attackedId).getPropiety()) {
        updateUnblockedUnits(constructionTiles.at(attackedId).getConstType());
    }
    attackBuildingReaction(attackedId, currentLife, totalLife);
}

/*
Pre-Condiciones: Setea el dinero del jugador para que se muestre en el
menu del mapa. 
Post-Condiciones: -
*/

void MapView::setMoney(int money) {
    if (actualMoney == money) {
        return;
    }
    menuTextsTranslator.erase("money");
    std::string text("Money: $" + std::to_string(money));
    menuTextsTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple("money"),
                          std::forward_as_tuple(&window, font, text));
    menuTexts.emplace(std::piecewise_construct,
                          std::forward_as_tuple("money"),
                          std::forward_as_tuple(&menuTextsTranslator.at
                          ("money"), 200, 32, 0, 0));
    actualMoney = money;
}

/*
Pre-Condiciones: Setea la energía del jugador para que se muestre en el
menu del mapa. 
Post-Condiciones: -
*/

void MapView::setEnergy(int energy) {
    if (actualEnergy == energy) return;
    menuTextsTranslator.erase("energy");
    std::string text("Energy: " + std::to_string(energy) + "%");
    menuTextsTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple("energy"),
                          std::forward_as_tuple(&window, font, text));
    menuTexts.emplace(std::piecewise_construct,
                          std::forward_as_tuple("energy"),
                          std::forward_as_tuple(&menuTextsTranslator.at
                          ("energy"), 200, 32, 0, 1));
    actualEnergy = energy;
}

/*
Pre-Condiciones: Renderiza el menu del mapa.
Post-Condiciones: -
*/

void MapView::renderMenu(Camera &cam) {
    cam.renderMenuRect();

    if (menuTextsTranslator.size() == 2) {
        cam.render(menuTexts.at("money"));
        cam.render(menuTexts.at("energy"));
    }

    for (MenuImage &image : menuImages) {
        cam.render(image);
    }
}

/*
Pre-Condiciones: Renderiza el mapa entero.
Post-Condiciones: -
*/

void MapView::render(Camera &cam) {
    renderMenu(cam);

    for (BackGroundTile &tile : backgroundTiles) {
        cam.render(tile);
    }
    if (worm.isAttacking()) {
        worm.render(cam, worm.getX(), worm.getY());
    }
    for (auto const& unit : unitTiles) {
        if (unitTiles.at(unit.first).getIsDead()) continue;
        int surpasses = unitTiles.at(unit.first).render(cam,
                                            unitTiles.at(unit.first).getX(),
                                            unitTiles.at(unit.first).getY());
        if (surpasses) {
            renderMenu(cam);
        }
    }
    for (auto const& building : constructionTiles) {
        if (constructionTiles.at(building.first).getIsDead()) continue;
        int surpasses = constructionTiles.at(building.first).render(cam,
                                constructionTiles.at(building.first).getX(),
                                constructionTiles.at(building.first).getY());
        if (surpasses) {
            renderMenu(cam);
        }
    }
}

/*
Pre-Condiciones: Actualiza el estado del mapa: si hay un gusano de arena,
unidades, construcciones.
Post-Condiciones: -
*/

void MapView::update(int delta) {
    if (worm.isAttacking()) {
        worm.update(delta);
    }
    for (auto const& unit : unitTiles) {
        unitTiles.at(unit.first).update(delta);
    }
    for (auto const& building : constructionTiles) {
        constructionTiles.at(building.first).update(delta);
    }
}

/*
Pre-Condiciones: Determina si el jugador clickeo en un edificio.
Post-Condiciones: Devuelve el id del edificio clickeado o -1 
en caso de que no se haya clickeado ningún edificio. 
*/

int MapView::isBuilding(int posX, int posY, bool propiety) {
    for (auto const& building : constructionTiles) {
        if ((posX >= constructionTiles.at(building.first).getX() *
             TILE_PIX_SIZE &&
            (posX <= (constructionTiles.at(building.first).getX() *
             TILE_PIX_SIZE +
            constructionTiles.at(building.first).getWidth()))) &&
            (posY >= constructionTiles.at(building.first).getY() *
             TILE_PIX_SIZE &&
            (posY <= (constructionTiles.at(building.first).getY() *
             TILE_PIX_SIZE +
            constructionTiles.at(building.first).getHeight()))) &&
            constructionTiles.at(building.first).getPropiety() == propiety) {
                return building.first;
        }
    }
    return -1;
}

/*
Pre-Condiciones: Determina si el jugador clickeo en una unidad.
Post-Condiciones: Devuelve el id de la unidad clickeada o -1 
en caso de que no se haya clickeado ninguna unidad. 
*/

int MapView::isUnit(int posX, int posY, bool propiety) {
    for (auto const& unit : unitTiles) {
        if ((posX >= unitTiles.at(unit.first).getX() * TILE_PIX_SIZE &&
            (posX <= (unitTiles.at(unit.first).getX() * TILE_PIX_SIZE +
            unitTiles.at(unit.first).getWidth()))) &&
            (posY >= unitTiles.at(unit.first).getY() * TILE_PIX_SIZE &&
            (posY <= (unitTiles.at(unit.first).getY() * TILE_PIX_SIZE +
            unitTiles.at(unit.first).getHeight()))) &&
            unitTiles.at(unit.first).getPropiety() == propiety) {
            return unit.first;
        }
    }
    return -1;
}

/*
Pre-Condiciones: Determina si una unidad esta bloqueada o no. 
Post-Condiciones: Devuelve true si esta bloqueada o false si no. 
*/

bool MapView::isBlocked(int currentUnit) {
    return menuImages[currentUnit].isBlocked();
}

/*
Pre-Condiciones: Determina si una unidad o edificio esta en construcción. 
Post-Condiciones: Devuelve true si esta en construcción o false si no. 
*/

bool MapView::isUnderConstruction(int current) {
    return menuImages[current].isCurrentlyUnderConstruction();
}

/*
Pre-Condiciones: Determina si un edificio ya esta listo para ser posicionado
(ya se construyó). 
Post-Condiciones: Devuelve true si esta listo o false si no. 
*/

bool MapView::isBuildingReady(int currentBuilding) {
    return menuImages[currentBuilding].isBuildingReady();
}

/*
Pre-Condiciones: Setea que el edificio no esta construido todavia. 
Post-Condiciones: -
*/

void MapView::setNotReady(int currentBuilding) {
    menuImages[currentBuilding].setNotReady();
}

/*
Pre-Condiciones: Maneja el ataque del gusano de arena. 
Post-Condiciones: -
*/

void MapView::wormAttack(int x, int y, std::vector<int> deadId) {
    float posX = static_cast<float>(x) / static_cast<float>(TILE_PIX_SIZE);
    float posY = static_cast<float>(y) / static_cast<float>(TILE_PIX_SIZE);
    for (int& id : deadId) {
        unitTiles.at(id).kill();
        // eliminarlos del arreglo o solo no renderizarlos?
        // lo mismo cuando mueren en ataque
        // lo mismo para muerte en ataque de edificio
    }
    worm.setNewPosition(posX, posY);
    worm.startAttacking();
}

/*
Pre-Condiciones: Actualiza la especia según el estado de la misma.
Post-Condiciones: -
*/

void MapView::updateSpecie(int x, int y, int state) {
    // si lo que cris me manda es el numero de tile tipo matriz
    int index = SPICE_OFFSET + state - 1;
    if (state == 0) index = 0;
    // int posX = x / 8;
    // int posY = y / 8;
    backgroundTiles[y * columns + x].changeTile(&(tileTextureTranslator.at(
                                                index)), x, y);
}

/*
Pre-Condiciones: Reproduce música en caso de que el jugador gane.
Post-Condiciones: -
*/

void MapView::playWinSound() {
    int offset = getSoundOffset();
    window.playSound(offset + WIN_SOUND, VOLUME);
}

/*
Pre-Condiciones: Reproduce música en caso de que el jugador pierda.
Post-Condiciones: -
*/

void MapView::playLostSound() {
    int offset = getSoundOffset();
    window.playSound(offset + LOST_SOUND, VOLUME);
}

/*
Pre-Condiciones: Destructor del MapView.
Post-Condiciones: -
*/

MapView::~MapView() {
}
