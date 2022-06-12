#include "map_item.h"
#include <QPixmap>
#include <QBitmap>
#include <cmath>
#include <iostream>

#define PIXELS 4
#define SPACING 32
#define CONST_YARD 40

MapItem::MapItem(int pix_row, int pix_column, std::string& path, int id) :
    row(pix_row),
    column(pix_column),
    path(path),
    id(id)
{
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

int MapItem::getId() {
    return id;
}

int MapItem::getHeight() {
    return height;
}

int MapItem::getWidth() {
    return width;
}
