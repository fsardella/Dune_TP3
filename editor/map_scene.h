#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
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
    void drawUnits();
    int distance(QPointF pos, QPointF newPos);
    bool isSpaced(QPointF nePos);
    bool isValidConstruction(QPointF pos);

private:
    Map* map;
    std::map<int, std::vector<std::string>> translator;
    std::vector<QPointF> constPixPositions;
    // current item
    std::string path = "../editor/tiles/sand_1.bmp"; // por ahi cambiarlo por objeto?
    int id = 0;

    int constYardAmount = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MAPSCENE_H
