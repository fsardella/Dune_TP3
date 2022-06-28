#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "BackGroundTile.h"
#include "Unit.h"
#include "Construction.h"
#include "MenuImage.h"
#include "yaml-cpp/yaml.h"
#include "MenuText.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <tuple>
#include <vector>

#define TILE_PIX_SIZE 32
#define IMAGE_PIX_WIDTH 100
#define IMAGE_PIX_HEIGHT 75

class MapView {
    SdlWindow& window;

    int houseNumberClient;
    size_t columns;
    size_t rows;

    // int actualMoney;
    // int actualEnergy;

    std::vector<BackGroundTile> backgroundTiles;
    std::map<int, Unit> unitTiles;
    std::map<int, Construction> constructionTiles;
    std::vector<MenuImage> menuImages;
    std::map<std::string, MenuText> menuTexts;

    std::map<int, std::vector<std::string>> tileInfoTranslator;

    std::map<int, SdlTexture> unitTextureTranslator;
    std::map<int, SdlTexture> tileTextureTranslator;
    std::map<int, SdlTexture> menuTextureTranslator;
    std::map<std::string, SdlTexture> menuTextsTranslator;
    std::map<int, SdlTexture> lifeTextureTranslator;

    std::map<int, std::map<std::tuple<int, int>, SdlTexture>> animationsRepository; 

    TTF_Font *font;

    public:
    MapView(SdlWindow& window, int houseNumberClient);
    void loadTileTranslator();
    void loadMenuTranslator();
    void loadSpritesTranslator();
    void loadLifeTranslator();
    void createMenu();
    void createUnit(int x, int y, int unitId, int unitType,
                    int playerId, int animationId, bool property);
    void getBuildingDimensions(int constType, int* width, int* height);
    void createConstruction(int x, int y, int constructionId, int constType,
                            bool property, int house);
    void createMap(int height, int width, std::vector<std::vector<uint8_t>> map);

    void attackUnit(int attackerId, int attackedId, int currentLife, int totalLife);
    void attackBuilding(int attackerId, int attackedId, int currentLife, int totalLife);

    void renderMenu(Camera &cam);
    void render(Camera& cam);
    void loadFontTitles();

    bool isBuilding(int posX, int posY, bool propiety);
    bool isUnit(int posX, int posY, bool propiety);

    bool isBlocked(int currentUnit);
    void updateBlockedUnits(int constType);

    void setMoney(int actualMoney);
    void setEnergy(int actualEnergy);

    void update(int delta);

    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;

    MapView(MapView&& other) ;
    MapView& operator=(MapView&& other) ;
    
    ~MapView();
};


#endif