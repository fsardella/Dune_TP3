#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map
{
    std::string name;
    int width = 0;
    int height = 0;
    int nPlayers = 0;
    bool isNew = true;
    std::vector<std::vector<int>> map;

public:
    Map();
    void setName(std::string& mapName);
    void setWidth(int mapWidth);
    void setHeight(int mapHeight);
    void setNPlayers(int mapNPlayers);
    void setIsNotNew();
    void setMap(std::vector<std::vector<int>> map); // posiblemente no ande

    std::string getName();
    int getWidth();
    int getHeight();
    int getNPlayers();
    bool getIsNew();
    std::vector<std::vector<int>> getMap();

    Map(const Map& other) = delete;
    Map& operator=(const Map& other) = delete;

    Map(Map&& other);
    Map& operator=(Map&& other);
};

#endif // MAP_H
