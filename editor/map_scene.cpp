#include "map_scene.h"
#include <math.h>
#include <iostream>

#define SPACING 32
#define CONST_YARD_ID 95
#define CONST_MID_POINT 48
#define CONST_PIXEL_SPACING 192
#define ROCK_NAME "rock"
#define SAND_NAME "sand"

MapScene::MapScene(Map* map, std::map<int,
                   std::vector<std::string>>& translator) :
    map(map),
    translator(translator) {
    drawInitialMap();
    drawGrid();
    drawUnits();

    if (!map->getIsNew()) {
        constYardAmount = map->getNPlayers();
    }
}

int MapScene::distance(QPointF pos, QPointF newPos) {
    return std::sqrt(std::pow(pos.x() - newPos.x(), 2) +
                     std::pow(pos.y() - newPos.y(), 2));
}

bool MapScene::isSpaced(QPointF newPos) {
    for (QPointF const& pos : constPixPositions) {
        if (distance(pos, newPos) < CONST_PIXEL_SPACING) {
            return false;
        }
    }
    return true;
}

bool MapScene::isValidConstruction(QPointF pos) {
    int x = static_cast<int>(pos.x());
    int y = static_cast<int>(pos.y());
    for (int i = x; i <= (x + (2 * SPACING)); i += SPACING) {
        for (int j = y; j <= (y + (2 * SPACING)); j += SPACING) {
            QPointF position(i, j);
            MapItem* item = qgraphicsitem_cast<MapItem*>(this->itemAt(position,
                                                         QTransform()));
            std::string itemName = translator[item->getId()][0];
            if (itemName.find(ROCK_NAME) == std::string::npos) {
                return false;
            }
        }
    }
    return true;
}

void MapScene::drawInitialMap() {
    std::vector<std::vector<int>> initialMap = map->getMap();
    for (int row = 0; row < map->getHeight(); row ++) {
        for (int column = 0; column < map->getWidth(); column ++) {
            int pixRow = row * SPACING;
            int pixCol = column * SPACING;
            int itemId = initialMap[row][column];

            std::string itemPath = translator[itemId][1];
            MapItem *item = new MapItem(pixRow, pixCol, itemPath, itemId);

            this->addItem(item);
        }
    }
}

void MapScene::drawGrid() {
    for (int i = 0; i <= (map->getWidth() * SPACING); i += SPACING) {
        this->addLine(i, 0, i, map->getHeight() * SPACING, QPen(Qt::darkGray));
    }
    for (int j = 0; j <= (map->getHeight() * SPACING); j += SPACING) {
        this->addLine(0, j, map->getWidth() * SPACING, j, QPen(Qt::darkGray));
    }
}

void MapScene::drawUnits() {
    std::vector<std::vector<int>> constYards = map->getConstYards();
    for (std::vector<int>& construction : constYards) {
        std::string constPath = translator[CONST_YARD_ID][1];
        MapItem *item = new MapItem(construction[0] * SPACING,
                                    construction[1] * SPACING, constPath,
                                    CONST_YARD_ID);
        this->addItem(item);
    }
}

void MapScene::setCurrentItem(std::string path, int id) {
    this->currentPath = path;
    this->currentId = id;
}

int MapScene::getConstYardAmount() {
    return constYardAmount;
}

bool MapScene::getDeleteMode() {
    return deleteMode;
}

void MapScene::setDeleteMode(bool mode) {
    deleteMode = mode;
}

void MapScene::handleDrawing(QPointF eventPos, MapItem* item) {
    std::string itemName = translator[item->getId()][0];
    if (itemName.find(SAND_NAME) == std::string::npos &&
        currentId != CONST_YARD_ID) return;

    int yRemainder = (static_cast<int>(eventPos.y()) % SPACING);
    int xRemainder = (static_cast<int>(eventPos.x()) % SPACING);

    QPointF newPos(eventPos.x() - xRemainder, eventPos.y() - yRemainder);

    MapItem* newItem = new MapItem(eventPos.y() - yRemainder,
                                   eventPos.x() - xRemainder,
                                   currentPath, currentId);

    int x = static_cast<int>(eventPos.x() / SPACING);
    int y = static_cast<int>(eventPos.y() / SPACING);

    if (currentId == CONST_YARD_ID) {
        if (constYardAmount == map->getNPlayers()) return;
        newPos += QPointF(CONST_MID_POINT, CONST_MID_POINT);
        if (isValidConstruction(eventPos) && isSpaced(newPos)) {
            this->addItem(newItem);
            constYardAmount++;
            map->addConst(y, x);
            constPixPositions.push_back(newPos);
            return;
        } else {
            delete newItem;
            return;
        }
    }
    if (item) {
        this->removeItem(item);
        delete item;
    }
    map->modifyMapAt(y, x, currentId);

    this->addItem(newItem);
}

void MapScene::removeConstYard(int x, int y) {
    int index = 0;
    for (size_t i = 0; i < constPixPositions.size(); i ++) {
        if (constPixPositions.at(i).x() == x &&
            constPixPositions.at(i).y() == y) {
           index = i;
        }
    }
    constPixPositions.erase(constPixPositions.begin() + index);
}

void MapScene::handleDeletion(QGraphicsSceneMouseEvent *event, MapItem* item) {
    if (item->getId() == CONST_YARD_ID) {
        constYardAmount--;
        this->removeConstYard(item->getCol() + CONST_MID_POINT,
                              item->getRow() + CONST_MID_POINT);
        this->removeItem(item);
        delete item;
        return;
    }

    std::string itemName = translator[item->getId()][0];
    if (itemName.find(SAND_NAME) != std::string::npos) return;

    int yRemainder = (static_cast<int>(event->scenePos().y()) % SPACING);
    int xRemainder = (static_cast<int>(event->scenePos().x()) % SPACING);

    std::string path(SAND_PATH);
    MapItem* newItem = new MapItem(event->scenePos().y() - yRemainder,
                                   event->scenePos().x() - xRemainder,
                                   path, SAND_ID);

    this->removeItem(item);
    delete item;

    int x = static_cast<int>(event->scenePos().x() / SPACING);
    int y = static_cast<int>(event->scenePos().y() / SPACING);

    map->modifyMapAt(y, x, SAND_ID);
    this->addItem(newItem);
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    MapItem* item = qgraphicsitem_cast<MapItem*>(this->itemAt(
                                                 event->scenePos(),
                                                 QTransform()));

    if (!item) {
        return;
    }

    if (deleteMode) {
        handleDeletion(event, item);
    } else {
        handleDrawing(event->scenePos(), item);
    }
}

void MapScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (deleteMode || currentId == CONST_YARD_ID) return;
    if (doubleClickCoordinateX == NONE_CLICK &&
        doubleClickCoordinateY == NONE_CLICK) {
        int yRemainder = (static_cast<int>(event->scenePos().y()) % SPACING);
        int xRemainder = (static_cast<int>(event->scenePos().x()) % SPACING);

        doubleClickCoordinateX = event->scenePos().x() - xRemainder;
        doubleClickCoordinateY = event->scenePos().y() - yRemainder;
        return;
    }
    int yRemainder = (static_cast<int>(event->scenePos().y()) % SPACING);
    int xRemainder = (static_cast<int>(event->scenePos().x()) % SPACING);
    int newX = event->scenePos().x() - xRemainder;
    int newY = event->scenePos().y() - yRemainder;


    int baseX = newX < doubleClickCoordinateX ? newX : doubleClickCoordinateX;
    int baseY = newY < doubleClickCoordinateY ? newY : doubleClickCoordinateY;
    int limX = newX < doubleClickCoordinateX ? doubleClickCoordinateX : newX;
    int limY = newY < doubleClickCoordinateY ? doubleClickCoordinateY : newY;

    for (int i = baseX; i <= limX; i += SPACING) {
        for (int j = baseY; j <= limY; j += SPACING) {
            QPointF cornerPos(i, j);
            QPointF itemPos(i + 2, j + 2);  // suma ficticia por grilla
            MapItem* item = qgraphicsitem_cast<MapItem*>(this->itemAt(
                                                         itemPos,
                                                         QTransform()));
            handleDrawing(cornerPos, item);
        }
    }

    doubleClickCoordinateX = NONE_CLICK;
    doubleClickCoordinateY = NONE_CLICK;
}
