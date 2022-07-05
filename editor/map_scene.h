#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <map>
#include <vector>
#include <string>
#include "map.h"
#include "map_item.h"

#define SAND_PATH "../editor/tiles/sand_1.bmp"
#define SAND_ID 0
#define NONE_CLICK -1

class MapScene : public QGraphicsScene {
 public:
    MapScene(Map* map, std::map<int, std::vector<std::string>>& translator);
    ~MapScene() = default;
    void setCurrentItem(std::string path, int id);
    int getConstYardAmount();
    bool getDeleteMode();
    void setDeleteMode(bool mode);

 private slots:
    void drawGrid();
    void drawInitialMap();
    void drawBuildings();
    int distance(QPointF pos, QPointF newPos);
    bool isSpaced(QPointF nePos);
    bool isValidConstruction(QPointF pos);
    void handleDrawing(QPointF eventPos, MapItem* item);
    void handleDeletion(QGraphicsSceneMouseEvent *event, MapItem* item);
    void removeConstYard(int x, int y);

 private:
    Map* map;
    std::map<int, std::vector<std::string>>& translator;
    std::vector<QPointF> constPixPositions;

    // current item
    std::string currentPath = SAND_PATH;
    int currentId = SAND_ID;

    int constYardAmount = 0;
    bool deleteMode = false;
    int doubleClickCoordinateX = NONE_CLICK;
    int doubleClickCoordinateY = NONE_CLICK;

 protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif  // MAPSCENE_H
