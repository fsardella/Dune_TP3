#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map {
    std::string name;
    int width = 0;
    int height = 0;
    int nPlayers = 0;
    bool isNew = true;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> constYards;

 public:
    Map();
    void setName(const std::string& mapName);
    void setWidth(int mapWidth);
    void setHeight(int mapHeight);
    void setNPlayers(int mapNPlayers);
    void setIsNotNew();
    void setMap(std::vector<std::vector<int>> map);
    void setConstYards(std::vector<std::vector<int>> constYards);

    void modifyMapAt(int row, int column, int id);
    void addConst(int row, int column);
    void deleteConst(int row, int column);

    std::string getName();
    int getWidth();
    int getHeight();
    int getNPlayers();
    bool getIsNew();
    std::vector<std::vector<int>> getMap();
    std::vector<std::vector<int>> getConstYards();

    Map(const Map& other) = delete;
    Map& operator=(const Map& other) = delete;

    Map(Map&& other);
    Map& operator=(Map&& other);
};

#endif  // MAP_H
