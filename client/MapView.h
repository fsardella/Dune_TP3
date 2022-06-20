#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include "Unit.h"
#include "BackGroundTile.h"
#include "Unit.h"
#include "MenuImage.h"
#include "yaml-cpp/yaml.h"
#include "MenuText.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TILE_PIX_SIZE 32
#define IMAGE_PIX_WIDTH 100
#define IMAGE_PIX_HEIGHT 75

class MapView {
    SdlWindow& window;

    int houseNumberClient;
    size_t columns;
    size_t rows;
    
    std::vector<BackGroundTile> backgroundTiles;
    std::vector<Unit> unitsTiles;
    std::vector<MenuImage> menuImages;
    std::map<std::string, MenuText> menuTexts;

    std::map<int, std::vector<std::string>> tileInfoTranslator;

    std::map<int, SdlTexture> unitTextureTranslator;
    std::map<int, SdlTexture> tileTextureTranslator;
    std::map<int, SdlTexture> menuTextureTranslator;
    std::map<std::string, SdlTexture> menuTextsTranslator;

    TTF_Font *font;

    public:
    MapView(SdlWindow& window, int houseNumberClient);
    void loadTileTranslator();
    void loadMenuTranslator();
    void createMenu();
    void createUnit(int x, int y, int unitType, int unitId);
    // void createUnit(int x, int y, int unitType, int unitId, int house, bool property);
    void createMap(int height, int width, std::vector<std::vector<int>> map);

    void renderMenu(Camera &cam);
    void render(Camera& cam);
    void loadFontTitles();

    void setMoney(int actualMoney);
    void setEnergy(int actualEnergy);

    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;

    MapView(MapView&& other) ;
    MapView& operator=(MapView&& other) ;
    
    ~MapView();
};


#endif