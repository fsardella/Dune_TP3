#include "map_scene.h"
#include <iostream>

#define SPACING 32 // mejorar nombre
#define CONST_YARD_ID 40
#define ROCK_ID 2
#define CONST_SPACING 3

MapScene::MapScene(Map* map, std::map<int, std::vector<std::string>> translator) :
    map(map),
    translator(translator)
{
    drawInitialMap();
    drawGrid();

    if (!map->getIsNew()) {
        constYardAmount = map->getNPlayers();
    }
}

void MapScene::fillWithRock(int pixRow, int pixCol) {
    std::string itemPath = translator[ROCK_ID][1];
    for (int i = pixRow; i <= (pixRow + (2 * SPACING)); i += SPACING) {
        for (int j = pixCol; j <= (pixCol + (2 * SPACING)); j += SPACING) {
            MapItem *item = new MapItem(i, j, itemPath, ROCK_ID);
            this->addItem(item);
        }
    }
}

void MapScene::fillMatrix(int row, int col, int id, int height, int width) {
    for (int i = row; i < row + height; i ++) {
        for (int j = col; j < col + width; j ++) {
            if (i == row && j == col) {
                map->modifyMapAt(i, j, id);
            } else {
                map->modifyMapAt(i, j, -1);
            }
        }
    }
}

bool MapScene::isSpaced(QPointF pos) {
    for (int i = 0; i < CONST_SPACING; i ++) {

    }
    for (int i = 0; i < CONST_SPACING; i ++) {

    }
}

bool MapScene::isValidConstruction(QPointF pos) {
    int x = (int) pos.x();
    int y = (int) pos.y();
    for (int i = x; i <= (x + (2 * SPACING)); i += SPACING) {
        for (int j = y; j <= (y + (2 * SPACING)); j += SPACING) {
            QPointF position(i, j);
            MapItem* item = qgraphicsitem_cast<MapItem*>(this->itemAt(position, QTransform()));
            std::string itemName = translator[item->getId()][0];
            if (itemName.find("rock") == std::string::npos) {
                return false;
            }
        }
    }
    return isSpaced(pos);
}

void MapScene::drawInitialMap() {
    std::vector<std::vector<int>> initialMap = map->getMap();
    for (int row = 0; row < map->getHeight(); row ++) {
        for (int column = 0; column < map->getWidth(); column ++) {
            int pixRow = row * SPACING;
            int pixCol = column * SPACING;
            int itemId = initialMap[row][column];
            if (itemId == -1) {
                continue;
            }
            std::string itemPath = translator[itemId][1];
            MapItem *item = new MapItem(pixRow, pixCol, itemPath, itemId);
            if (itemId == CONST_YARD_ID) { // rellenar con roca antes
                fillWithRock(pixRow, pixCol);
            }
            this->addItem(item);
        }
    }
}

void MapScene::drawGrid() {
    for(int i = 0; i <= (map->getWidth() * SPACING); i += SPACING) {
        this->addLine(i, 0, i, map->getHeight() * SPACING, QPen(Qt::darkGray));
    }
    for(int j = 0; j <= (map->getHeight() * SPACING); j += SPACING) {
        this->addLine(0, j, map->getWidth() * SPACING, j, QPen(Qt::darkGray));
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

    int yRemainder = (int (event->scenePos().y()) % SPACING);
    int xRemainder = (int (event->scenePos().x()) % SPACING);
    MapItem* newItem = new MapItem(event->scenePos().y() - yRemainder, event->scenePos().x() - xRemainder, path, id);
    std::string newName = translator[id][0];

    int y = static_cast<int>(event->scenePos().y() / SPACING);
    int x = static_cast<int>(event->scenePos().x() / SPACING);

    if (newName.compare("construction yard") == 0) {
        if (isValidConstruction(event->scenePos())) {
            fillMatrix(y, x, id, newItem->getHeight(), newItem->getWidth());
            this->addItem(newItem);
            constYardAmount++;
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
    fillMatrix(y, x, id, newItem->getHeight(), newItem->getWidth());

    this->addItem(newItem);
}
