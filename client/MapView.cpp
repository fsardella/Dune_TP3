#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include "MapView.h"
#include "Camera.h"

#define TILESAMOUNT 40
/*
MapView::MapView(SdlWindow& window,
                 YAML::Node& clientConfig)
: window(window),
  clientConfig(clientConfig),
  columns(0),
  rows(0) {
    this->loadTranslator();
}

*/
MapView::MapView(SdlWindow& window)
: window(window),
  columns(0),
  rows(0) {
    this->loadTranslator();
}
/*
void MapView::loadMap(const std::string &mapFile) {
    try {
        map = YAML::LoadFile(mapFile);
    } catch (const std::exception& e) {
        throw e;
    }
    columns = map["size_columns"].as<size_t>();
    rows = map["size_rows"].as<size_t>();
    loadBackground();
}
*/

void MapView::loadTranslator() {
    YAML::Node node = YAML::LoadFile("../tiles.yaml");
    for (int i = 0; i <= 0; i++) {
        std::vector<std::string> tileInfo = node[i].as<std::vector<std::string>>();
        tileInfoTranslator[i] = tileInfo;
    }
    for (int i = 0; i <= 0; i++) {
        std::string tileSizeKey(std::to_string(i) + " size");
        std::vector<int> tileSize = node[tileSizeKey].as< std::vector<int>>();
        tileSizeTranslator[i] = tileSize;
    }
}

void MapView::createMap(int height, int width, std::vector<std::vector<int>> map) {
    columns = width;
    rows = height;
    for (size_t i = 0; i < rows; i ++) {
        for(size_t j = 0; j < columns; j++) {
            std::vector<std::string> tileInfo = tileInfoTranslator[map[i][j]];
            std::vector<int> tileSize = tileSizeTranslator[map[i][j]];
            textureTranslator.emplace(std::piecewise_construct,
                          std::forward_as_tuple(map[i][j]),
                          std::forward_as_tuple(tileInfo[1], window));
            auto& backgroundTexture = textureTranslator.at(map[i][j]);
            backgroundTiles.emplace_back(backgroundTexture, tileSize[0]*4, tileSize[1]*4, j, i);
        }
    }
}
/*
void MapView::loadBackground() {
    std::string background = map["background"].as<std::string>();
    std::string backgroundPath;
    std::vector<std::vector<std::string>> backgrounds = clientConfig["background"].as<std::vector<std::vector<std::string>>>();

    for (std::vector<std::string>& vector : backgrounds) {
        if (vector[0] == background) { //si el primer elemento de alguno de los vectores de background es igual al nombre del background requerido, es true
            backgroundPath = vector[1]; // por lo tanto, el segundo elemento de alguno de esos vectores va a ser el path que se necesita
            break;
        }
    }

    textureHolder.emplace(std::piecewise_construct,
                          std::forward_as_tuple("background"),
                          std::forward_as_tuple(backgroundPath, window));

    auto& backgroundTexture = textureHolder.at("background");
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            backgroundTiles.emplace_back(backgroundTexture, 32, 32, i, j); //llena el vector con un objeto construyendolo con sus argumentos
}*/
/*
void MapView::loadUnit(int x, int y) {
    std::string unit = map["unit"].as<std::string>();
    std::string unitPaths;
    std::vector<std::vector<std::string>> units = clientConfig["unit"].as<std::vector<std::vector<std::string>>>();
    for (std::vector<std::string>& vector: units) {
        if (vector[0] == unit) {
            unitPaths = vector[1];
            break;
        }
    }

    textureHolder.emplace(std::piecewise_construct,
                          std::forward_as_tuple("unit"),
                          std::forward_as_tuple(unitPaths, window, false));

    auto& unitTexture = textureHolder.at("unit");
    for (int i = 0; i < 1; ++i)
        for (int j = 0; j < 1; ++j) // ver de poner x e y para que se imprima donde yo quiero
            unitsTiles.emplace_back(unitTexture, 100, 100 , x, y); //llena el vector con un objeto construyendolo con sus argumentos
}
*/
MapView::~MapView() {
}

// void MapView::render(Camera &cam) {
//     for (NonMovable &tile : backgroundTiles) {
//         cam.render(tile, 0);
//     }
//     for (NonMovable &unit : unitsTiles) {
//         cam.render(unit, unit.getX(), unit.getY());
//     }
// }

void MapView::render(Camera &cam) {
    for (BackGroundTile &tile : backgroundTiles) {
            cam.render(tile, 0);
    }
    /*for (NonMovable &unit : unitsTiles) {
        cam.render(unit, unit.getX(), unit.getY());
    }*/
}