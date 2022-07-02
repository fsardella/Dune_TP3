#include "map_scene.h"
#include <math.h>
#include <iostream>

#define SPACING 32
#define CONST_YARD_ID 95
#define CONST_MID_POINT 48
#define CONST_PIXEL_SPACING 192
#define ROCK_NAME "rock"
#define SAND_NAME "sand"

/*
 * Pre-condiciones: Constructor de la clase MapScene a partir de un puntero
 * a un objeto de la clase Map y un diccionario traductor. Dibuja la grilla
 * el mapa inciial, la grilla y los centros de construcción (en caso de que
 * existan).
 * Post-condiciones: -
 * */

MapScene::MapScene(Map* map, std::map<int,
                   std::vector<std::string>>& translator) :
    map(map),
    translator(translator) {
    drawInitialMap();
    drawGrid();
    drawBuildings();

    if (!map->getIsNew()) {
        constYardAmount = map->getNPlayers();
    }
}

/*
 * Pre-condiciones: Recibe dos puntos de clase QPointF.
 * Post-condiciones: Devuelve un entero que representa la distancia
 * en pixel entre los dos puntos.
 * */

int MapScene::distance(QPointF pos, QPointF newPos) {
    return std::sqrt(std::pow(pos.x() - newPos.x(), 2) +
                     std::pow(pos.y() - newPos.y(), 2));
}

/*
 * Pre-condiciones: Recibe un punto de clase QPointF.
 * Post-condiciones: Devuelve true si la distancia entre
 * ese punto y los centros de cada centro de construcción creado
 * supera el espacio de distanciamiento requerido. Devuelve
 * false en caso contrario.
 * */

bool MapScene::isSpaced(QPointF newPos) {
    for (QPointF const& pos : constPixPositions) {
        if (distance(pos, newPos) < CONST_PIXEL_SPACING) {
            return false;
        }
    }
    return true;
}

/*
 * Pre-condiciones: Recibe un punto de clase QPointF.
 * Post-condiciones: Devuelve true si sobre el cuadrado donde se quiere
 * construir un centro de construcción tiene roca debajo. False en caso
 * contrario.
 * */

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

/*
 * Pre-condiciones: Dibuja el mapa inicial por pantalla.
 * Post-condiciones: -
 * */

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

/*
 * Pre-condiciones: Dibuja una grilla sobre el mapa dibujado.
 * Post-condiciones: -
 * */

void MapScene::drawGrid() {
    for (int i = 0; i <= (map->getWidth() * SPACING); i += SPACING) {
        this->addLine(i, 0, i, map->getHeight() * SPACING, QPen(Qt::darkGray));
    }
    for (int j = 0; j <= (map->getHeight() * SPACING); j += SPACING) {
        this->addLine(0, j, map->getWidth() * SPACING, j, QPen(Qt::darkGray));
    }
}

/*
 * Pre-condiciones: Dibuja los centros de construcción creados (si existen).
 * Post-condiciones: -
 * */

void MapScene::drawBuildings() {
    std::vector<std::vector<int>> constYards = map->getConstYards();
    for (std::vector<int>& construction : constYards) {
        std::string constPath = translator[CONST_YARD_ID][1];
        MapItem *item = new MapItem(construction[0] * SPACING,
                                    construction[1] * SPACING, constPath,
                                    CONST_YARD_ID);
        this->addItem(item);
    }
}

/*
 * Pre-condiciones: Recibe el path a un archivo (imagen) y un número de id.
 * Setea esos datos para representar el item actualmente seleccionado.
 * Post-condiciones: -
 * */

void MapScene::setCurrentItem(std::string path, int id) {
    this->currentPath = path;
    this->currentId = id;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un entero representando la cantidad de centros
 * de construcción creados.
 * */

int MapScene::getConstYardAmount() {
    return constYardAmount;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve true si la escena se encuentra actualmente en
 * modo delete, false en caso contrario.
 * */

bool MapScene::getDeleteMode() {
    return deleteMode;
}

/*
 * Pre-condiciones: Recibe un booleano que con true representa que la escena
 * se encuentra en modo delelte o con false que no. Lo setea en uno de sus
 * atributos.
 * Post-condiciones: -
 * */

void MapScene::setDeleteMode(bool mode) {
    deleteMode = mode;
}

/*
 * Pre-condiciones: Función encargada de manejar el accionar cuando se quiere
 * dibujar (insertar items) en el mapa. Valida el intento y si es correcto
 * crea un nuevo item y lo asigna al mapa.
 * Post-condiciones: -
 * */

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

/*
 * Pre-condiciones: Elimina el centro de construcción cuyo centro se encontraba
 * en la coordenada x e y recibida.
 * Post-condiciones: -
 * */

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

/*
 * Pre-condiciones: Función encargada de manejar el accionar cuando se quiere
 * eliminar un item del mapa. Valida el intento y si es correcto
 * elimina el item. En su reemplazo crea un item de tipo arena y lo agrega al
 * mapa (si no es un centro de construcción lo que se intenta eliminar).
 * Post-condiciones: -
 * */

void MapScene::handleDeletion(QGraphicsSceneMouseEvent *event, MapItem* item) {
    if (item->getId() == CONST_YARD_ID) {
        constYardAmount--;
        int constX = static_cast<int>(event->scenePos().x() / SPACING);
        int constY = static_cast<int>(event->scenePos().y() / SPACING);
        map->deleteConst(constX, constY);
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

/*
 * Pre-condiciones: Función encargada de manejar el click del usuario sobre
 * el mapa. Llama a los manejadores correspondientes dependiendo de si la
 * escena se encuentra en modo delete o no.
 * Post-condiciones: -
 * */

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

/*
 * Pre-condiciones: Función encargada de manejar el doble click del usuario
 * sobre el mapa. Inserta tantos items como lugar haya en el area formada
 * por dos puntos (esquina superior izquierda y esquina inferior derecha) que
 * surgen de dos doble clicks consecutivos.
 * Post-condiciones: -
 * */

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
