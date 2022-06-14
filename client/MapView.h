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
    std::map<std::string, SdlTexture> unitTranslator;
    std::map<int, SdlTexture> textureTranslator;
    public:
    MapView(SdlWindow& window);
    void loadMap(const std::string &mapFile);
    void createUnit(int x, int y, std::string unitType, int unitId);
    void loadBackground();
    void loadTranslator();
    void createMap(int height, int width, std::vector<std::vector<int>> map);
    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;
    void render(Camera& cam);
    MapView(MapView&& other) ;
    MapView& operator=(MapView&& other) ;
    ~MapView();
};


#endif