#ifndef __MAPVIEW_H__
#define __MAPVIEW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <tuple>
#include <vector>
#include <map>
#include <string>
#include "BackGroundTile.h"
#include "Unit.h"
#include "Construction.h"
#include "MenuImage.h"
#include "yaml-cpp/yaml.h"
#include "MenuText.h"
#include "Worm.h"

#define TILE_PIX_SIZE 32
#define IMAGE_PIX_WIDTH 100
#define IMAGE_PIX_HEIGHT 75
#define ATTACK_VOLUME 60
#define VOICE_VOLUME 80
#define WIN_SOUND 1
#define LOST_SOUND 0

class MapView {
    SdlWindow& window;

    int houseNumberClient;
    int identifier;
    size_t columns;
    size_t rows;

    int actualMoney;
    int actualEnergy;

    Worm worm;

    std::vector<BackGroundTile> backgroundTiles;
    std::map<int, Unit> unitTiles;
    std::map<int, Construction> constructionTiles;
    std::vector<MenuImage> menuImages;
    std::map<std::string, MenuText> menuTexts;

    std::map<int, std::vector<std::string>> tileInfoTranslator;
    std::map<int, std::vector<int>> menuInfoHouses;

    std::map<int, SdlTexture> unitTextureTranslator;
    std::map<int, SdlTexture> tileTextureTranslator;
    std::map<int, SdlTexture> menuTextureTranslator;
    std::map<int, SdlTexture> wormTextureTranslator;
    std::map<std::string, SdlTexture> menuTextsTranslator;
    std::map<int, SdlTexture> lifeTextureTranslatorForUnit;
    std::map<int, SdlTexture> lifeTextureTranslatorForConstruction;
    std::map<std::tuple<int, int>, SdlTexture> attackTextureTranslator;

    std::map<int, SdlTexture> identifierTranslator;

    std::map<int, std::map<std::tuple<int, int>,
             SdlTexture>> animationsRepository;

    TTF_Font *font;

 public:
    MapView(SdlWindow& window, int houseNumberClient);
    void loadTileTranslator();
    void loadMenuTranslator();
    void loadSpritesTranslator();
    void loadLifeTranslator();
    void loadAttackTranslator();
    void loadIdentifierTranslator();
    void loadWormTranslator();
    std::vector<SdlTexture*> wormEmptyTexturesInitializer();
    void wormTexturesInitializer();
    void createMenu();
    void createUnit(int x, int y, int unitId, int unitType,
                    int playerId, int animationId, bool propiety);
    void getBuildingDimensions(int constType, int* width, int* height);
    void createConstruction(int x, int y, int playerId, int constructionId,
                            int constType, bool propiety, int house);
    void createMap(int height, int width,
                   std::vector<std::vector<uint8_t>> map);

    void attackUnit(int attackerId, int attackedId, int currentLife,
                    int totalLife);
    void attackBuilding(int attackerId, int attackedId, int currentLife,
                        int totalLife);
    void attackUnitReaction(int attackedId, int currentLife, int totalLife);
    void attackBuildingReaction(int attackedId, int currentLife, int totalLife);

    void renderMenu(Camera &cam);
    void render(Camera& cam);
    void loadFontTitles();

    int isBuilding(int posX, int posY, bool propiety);
    int isUnit(int posX, int posY, bool propiety);

    bool isBlocked(int currentUnit);
    void updateBlockedUnits(int constType, int house);
    void updateUnblockedUnits(int constType);

    bool isUnderConstruction(int current);
    bool isBuildingReady(int currentBuilding);
    void setNotReady(int currentBuilding); // eliminar
    void updateUnready(int constructionId, int property);

    void wormAttack(int x, int y);

    void updateProgress(int menuId, int progress);

    void setMoney(int actualMoney);
    void setEnergy(int actualEnergy);

    void touchedUnit(int unitId);
    void untouchedUnit(int unitId);
    int getType(int unitId);
    void touchedMenuImage(int currentMenuImage, bool state);

    void update(int delta);

    int getSoundOffset();
    void playWinSound();
    void playLostSound();

    void updateSpecie(int x, int y, int state);

    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;

    MapView(MapView&& other);
    MapView& operator=(MapView&& other);

    ~MapView();
};

#endif /*__MAPVIEW_H__*/
