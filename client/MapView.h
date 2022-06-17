#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include "Unit.h"
#include "BackGroundTile.h"
#include "yaml-cpp/yaml.h"
#include "Unit.h"

class MapView {
    SdlWindow& window;
    std::vector<BackGroundTile> backgroundTiles;
    std::vector<Unit> unitsTiles;

    size_t columns;
    size_t rows;

    std::map<int, std::vector<std::string>> tileInfoTranslator;
    std::map<int, std::vector<int>> tileSizeTranslator;

    std::map<int, SdlTexture> unitTextureTranslator;
    std::map<int, SdlTexture> tileTextureTranslator;
    std::map<int, SdlTexture> menuTextureTranslator;

    public:
    MapView(SdlWindow& window);
    void loadTileTranslator();
    void loadMenuTranslator();
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