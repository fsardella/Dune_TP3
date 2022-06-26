#include "map_scene.h"
#include <math.h>
#include <iostream>

#define SPACING 32
#define CONST_YARD_ID 95
#define CONST_MID_POINT 48
#define CONST_PIXEL_SPACING 192
#define ROCK_NAME "rock"
#define SAND_NAME "sand"

// Lo que se pueda de acá, por referencia
MapScene::MapScene(Map* map, std::map<int, std::vector<std::string>> translator) :
    map(map),
    translator(translator)
{
    drawInitialMap();
    drawGrid();
    drawUnits();

    if (!map->getIsNew()) {
        constYardAmount = map->getNPlayers();
    }
}

int MapScene::distance(QPointF pos, QPointF newPos) {
    return std::sqrt(std::pow(pos.x() - newPos.x(), 2) + std::pow(pos.y() - newPos.y(), 2));
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
    int x = (int) pos.x();
    int y = (int) pos.y();
    for (int i = x; i <= (x + (2 * SPACING)); i += SPACING) {
        for (int j = y; j <= (y + (2 * SPACING)); j += SPACING) {
            QPointF position(i, j);
            MapItem* item = qgraphicsitem_cast<MapItem*>(this->itemAt(position, QTransform()));
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
    this->path = path;
    this->id = id;
}

int MapScene::getConstYardAmount() {
    return constYardAmount;
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    MapItem* item = qgraphicsitem_cast<MapItem*>(this->itemAt(event->scenePos(), QTransform()));

    if (!item) {
        return;
    }

    std::string itemName = translator[item->getId()][0];
    if (itemName.find(SAND_NAME) == std::string::npos && id != CONST_YARD_ID) return;

    int yRemainder = (int (event->scenePos().y()) % SPACING);
    int xRemainder = (int (event->scenePos().x()) % SPACING);

    QPointF newPos(event->scenePos().x() - xRemainder, event->scenePos().y() - yRemainder);

    MapItem* newItem = new MapItem(event->scenePos().y() - yRemainder, event->scenePos().x() - xRemainder, path, id);
    // ojo que esto no lo usan
    std::string newName = translator[id][0];

    int x = static_cast<int>(event->scenePos().x() / SPACING);
    int y = static_cast<int>(event->scenePos().y() / SPACING);

    if (id == CONST_YARD_ID) {
        if (constYardAmount == map->getNPlayers()) return;
        newPos += QPointF(CONST_MID_POINT, CONST_MID_POINT);
        if (isValidConstruction(event->scenePos()) && isSpaced(newPos)) {
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
    map->modifyMapAt(y, x, id);

    this->addItem(newItem);
}
