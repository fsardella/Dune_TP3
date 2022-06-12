#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <set>
#include "map.h"
#include "map_item.h"

class MapScene : public QGraphicsScene {
public:
    MapScene(Map* map, std::map<int, std::vector<std::string>> translator);
    ~MapScene() = default;
    void setCurrentItem(std::string path, int id);
    int getConstYardAmount();

private slots:
    void drawGrid();
    void drawInitialMap();
    void fillWithRock(int pixRow, int pixCol);
    bool isSpaced(QPointF pos);
    bool isValidConstruction(QPointF pos);
    void fillMatrix(int row, int col, int id, int height, int width);

private:
    Map* map;
    std::map<int, std::vector<std::string>> translator;
    std::set<QPointF> constPositions;
    // current item
    std::string path = "/home/florencia/taller/repo_grupo/imgs/small_sand.bmp"; // por ahi cambiarlo por objeto?
    int id = 0;
    int constYardAmount = 0;
    std::vector<std::tuple<int, int>> constYarsPos; // chequear que esten a 3 bloques

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MAPSCENE_H
