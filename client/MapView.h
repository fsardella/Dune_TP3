#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include "NonMovable.h"
#include "yaml-cpp/yaml.h"
#include "Unit.h"

class MapView {
    SdlWindow& window;
    std::vector<NonMovable> backgroundTiles;
    std::vector<NonMovable> unitsTiles;
    YAML::Node& clientConfig;
    YAML::Node map;
    size_t columns;
    size_t rows;
    std::map<std::string, SdlTexture> textureHolder;
    public:
    MapView(SdlWindow& window,
            YAML::Node& clientConfig);
    void loadMap(const std::string &mapFile);
    void loadUnit(int x, int y);
    void loadBackground();
    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;
    void render(Camera& cam);
    MapView(MapView&& other) ;
    MapView& operator=(MapView&& other) ;
    ~MapView();
};


#endif