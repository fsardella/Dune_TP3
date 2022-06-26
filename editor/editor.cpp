#include "editor.h"
#include "ui_editor.h"

#include <iostream>
#include <QPushButton>
#include <QMessageBox>

#define DUNE_OFFSET 3
#define ROCK_OFFSET 6
#define SPICE_OFFSET 22
#define MONT_OFFSET 29
#define CLIFF_OFFSET 63
#define CY_OFFSET 95

Editor::Editor(Map* map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor),
    map(map)
{
    ui->setupUi(this);

    std::string yamlPath(map->getName() + ".yaml");
    parser = YamlParser(yamlPath);

    translator = parser.getTranslator();

    configureInitialMap();

    layout = new QHBoxLayout();
    rightLayout = new QVBoxLayout();
    drawMap();
    layout->addLayout(rightLayout);
    setOptions();
    setSaveButton();
    this->setLayout(layout);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::configureInitialMap() {
    try {
        parser.getMap(map);
    } catch(const std::ios_base::failure& e) { // creas uno nuevo con arena
        std::vector<std::vector<int>> initialMap;
        for (int i = 0; i < map->getHeight(); i ++) {
            std::vector<int> row;
            for (int j = 0; j < map->getWidth(); j ++) {
                row.push_back(0);
            }
            initialMap.push_back(row);
        }
        map->setMap(initialMap);
    }
}

void Editor::drawMap() {
    mapScene = new MapScene(map, translator);
    QGraphicsView* mapView = new QGraphicsView();
    mapView->setScene(mapScene);

    mapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(mapView);
}

void Editor::setOptions() {
    tilesList = new TilesList(nullptr);
    rightLayout->addWidget(tilesList);
    connect(tilesList, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(tilesListClicked(QTreeWidgetItem*,int)));
}

void Editor::setSaveButton() {
    QPushButton *savePushButton = new QPushButton("Save", this);
    rightLayout->addWidget(savePushButton, 2);

    connect(savePushButton, SIGNAL (released()), this, SLOT (handleSaveButton()));
}

int Editor::getItemId(std::string parentType, std::string name) {
    int n = parser.getItemId(parentType, name);
    if (parentType.compare("sand") == 0) {
        return n;
    } else if(parentType.compare("rock") == 0) {
        return n + ROCK_OFFSET;
    } else if(parentType.compare("dune") == 0) {
        return n + DUNE_OFFSET;
    } else if (parentType.compare("spice") == 0) {
        return n + SPICE_OFFSET;
    } else if (parentType.compare("mont") == 0) {
        return n + MONT_OFFSET;
    } else if (parentType.compare("cliff") == 0) {
        return n + CLIFF_OFFSET;
    } else {
        return CY_OFFSET;
    }
}

void Editor::tilesListClicked(QTreeWidgetItem* item, int column) {
    if(item->childCount() == 0) { // si no soy root
        std::string nameItem = item->text(0).toStdString();
        QTreeWidgetItem* parent = item->parent();
        std::string parentType = parent->text(0).toStdString();

        int id = getItemId(parentType, nameItem);
        std::string path = translator[id][1];
        mapScene->setCurrentItem(path, id);

    }
}

void Editor::handleSaveButton() {
    if (mapScene->getConstYardAmount() == map->getNPlayers()) {
        parser.saveMap(map);
        QMessageBox::information(this, tr("Saved"), tr("Mas was saved correctly"));
    } else {
        std::string msg("Map should have " + std::to_string(map->getNPlayers()) + " construction yards");
        QMessageBox::warning(this, tr("Can´t save"), tr(msg.c_str()), QMessageBox::Close);
    }
}
