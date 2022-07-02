#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsPixmapItem>
#include <string>

class MapItem : public QGraphicsPixmapItem {
 private:
        int row;
        int column;
        std::string path;
        int id;
        int height;
        int width;

 public:
        MapItem(int pix_row, int pix_column, std::string& path, int id);
        ~MapItem() = default;
        int getId();
        int getHeight();
        int getWidth();
        int getRow();
        int getCol();
};

#endif  // MAPITEM_H
