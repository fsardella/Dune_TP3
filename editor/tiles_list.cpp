#include "tiles_list.h"
#include <map>
#include <vector>
#include "yaml_parser.h"

#define SAND "sand"
#define DUNE "dune"
#define ROCK "rock"
#define SPICE "spice"
#define MONT "mont"
#define CLIFF "cliff"
#define CONSTRUCTION_YARD "construction yard"

TilesList::TilesList(QWidget *parent) :
    QTreeWidget(parent) {
    this->setHeaderLabel("Tile options");
    this->setTiles();
}


void TilesList::setTiles() {
    std::vector<std::string> types {SAND, DUNE, ROCK, SPICE, MONT,
                                    CLIFF, CONSTRUCTION_YARD};
    YamlParser parser;
    for (std::string& type : types) {
        QTreeWidgetItem* root = new QTreeWidgetItem();
        root->setText(0, QString::fromStdString(type));
        this->addTopLevelItem(root);
        std::map<std::string, std::string> items = parser.getItems(type);
        for (auto& item : items) {
            std::string name = item.first;
            std::string path = item.second;
            QPixmap pixmap(QString::fromStdString(path));

            QSize size = pixmap.size();
            pixmap.scaled(size.width() * 4, size.height() * 4);

            QIcon icon(pixmap);
            add_child(root, name, icon);
        }
    }
}

void TilesList::add_child(QTreeWidgetItem* parent, std::string& name,
                          QIcon icon) {
    QTreeWidgetItem* child = new QTreeWidgetItem();
    child->setText(0, QString::fromStdString(name));
    child->setIcon(0, icon);
    parent->addChild(child);
}
