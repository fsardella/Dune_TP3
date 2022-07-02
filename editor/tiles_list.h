#ifndef TILESLIST_H
#define TILESLIST_H

#include <QTreeWidget>
#include <string>

class TilesList : public QTreeWidget {
    Q_OBJECT

 public:
    explicit TilesList(QWidget *parent = nullptr);
    ~TilesList() = default;

 private:
    void setTiles();
    void add_child(QTreeWidgetItem* parent, std::string& name, QIcon icon);
};

#endif  // TILESLIST_H
