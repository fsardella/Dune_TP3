#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <vector>
#include <string>
#include <map>
#include "map.h"
#include "yaml_parser.h"
#include "tiles_list.h"
#include "map_scene.h"

namespace Ui {
class Editor;
}

class Editor : public QDialog {
    Q_OBJECT

 public:
    explicit Editor(Map* map, QWidget *parent = nullptr);
    ~Editor();


 private slots:
    void configureInitialMap();
    void drawMap();
    void setOptions();
    void tilesListClicked(QTreeWidgetItem* tile, int column);
    int getItemId(std::string parentType, std::string name);
    void setSaveButton();
    void handleSaveButton();
    void handleDeleteButton();

 private:
    Ui::Editor *ui;
    Map* map;
    YamlParser parser;
    QHBoxLayout* layout;
    QVBoxLayout* rightLayout;
    TilesList* tilesList;
    MapScene* mapScene;
    std::map<int, std::vector<std::string>> translator;
};

#endif  // EDITOR_H
