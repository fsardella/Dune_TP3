#include "map_item.h"
#include <QPixmap>
#include <QBitmap>
#include <cmath>

#define PIXELS 4
#define SPACING 32
#define CONST_YARD 95

/*
 * Pre-condiciones: Constructor de la clase MapItem a partir de un número
 * de fila, un número de columna, un path a un archivo y un id.
 * Post-condiciones: -
 * */

MapItem::MapItem(int pix_row, int pix_column, std::string& path, int id) :
    row(pix_row),
    column(pix_column),
    path(path),
    id(id) {
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    QPixmap pixmap(QString::fromStdString(path));
    height = (pixmap.height() / 8);
    width = (pixmap.width() / 8);
    pixmap = pixmap.scaled(pixmap.width() * PIXELS, pixmap.height() * PIXELS);

    if (id == CONST_YARD) {
        QBitmap bitmap = pixmap.createMaskFromColor(Qt::black);
        pixmap.setMask(bitmap);
    }

    this->setPixmap(pixmap);
    this->setPos(pix_column, pix_row);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el id del item.
 * */

int MapItem::getId() {
    return id;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve la altura del item.
 * */

int MapItem::getHeight() {
    return height;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve al ancho del item.
 * */

int MapItem::getWidth() {
    return width;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve la fila en donde se encuentra el item.
 * */

int MapItem::getRow() {
    return row;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve la columna en donde se encuentra el item.
 * */

int MapItem::getCol() {
    return column;
}
