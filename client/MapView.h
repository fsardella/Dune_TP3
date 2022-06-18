#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include "Unit.h"
#include "BackGroundTile.h"
#include "Unit.h"
#include "MenuImage.h"
#include "yaml-cpp/yaml.h"

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

    std::map<int, std::vector<std::string>> tileInfoTranslator;

    std::map<int, SdlTexture> unitTextureTranslator;
    std::map<int, SdlTexture> tileTextureTranslator;
    std::map<int, SdlTexture> menuTextureTranslator;

    public:
    MapView(SdlWindow& window, int houseNumberClient);
    void loadTileTranslator();
    void loadMenuTranslator();
    void createMenu();
    void createUnit(int x, int y, int unitType, int unitId);
    // void createUnit(int x, int y, int unitType, int unitId, int house, bool property);
    void createMap(int height, int width, std::vector<std::vector<int>> map);

    void render(Camera& cam);

    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;

    MapView(MapView&& other) ;
    MapView& operator=(MapView&& other) ;
    
    ~MapView();
};


#endif