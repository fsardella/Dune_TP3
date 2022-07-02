#include "editor.h"
#include <QMessageBox>
#include <QPushButton>
#include "ui_editor.h"

#define DUNE_OFFSET 3
#define ROCK_OFFSET 6
#define SPICE_OFFSET 22
#define MONT_OFFSET 29
#define CLIFF_OFFSET 63
#define CY_OFFSET 95

/*
 * Pre-condiciones: Constructor de la clase Editor (ventana de qt para la
 * edición de un mapa). Recibe un objeto de clase Map, quien tiene los datos
 * recolectados que ingreso el usuario.
 * Post-condiciones: -
 * */

Editor::Editor(Map* map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor),
    map(map) {
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
    setButtons();
    this->setLayout(layout);
}

/*
 * Pre-condiciones: Destrcutor de la clase Editor.
 * Post-condiciones: -
 * */

Editor::~Editor() {
    delete ui;
}

/*
 * Pre-condiciones: Configura el mapa incial. En caso de creación
 * setea al mapa como una matriz de arenas. En caso de edición carga
 * el mapa de un archivo con extensión .yaml.
 * Post-condiciones: -
 * */

void Editor::configureInitialMap() {
    try {
        parser.getMap(map);
    } catch(const std::ios_base::failure& e) {
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

/*
 * Pre-condiciones: Grafica el mapa por pantalla. Lo hace a partir
 * de una nueva clase MapView que recibe una clase MapScene.
 * Post-condiciones: -
 * */

void Editor::drawMap() {
    mapScene = new MapScene(map, translator);
    QGraphicsView* mapView = new QGraphicsView();
    mapView->setScene(mapScene);

    mapView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(mapView);
}

/*
 * Pre-condiciones: Muestra por pantalla una lista de las posibles
 * tiles a incorporar en el mapa. Configura un manejador de clicks
 * del usuario sobre la lista.
 * Post-condiciones: -
 * */

void Editor::setOptions() {
    tilesList = new TilesList(nullptr);
    rightLayout->addWidget(tilesList);
    connect(tilesList, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this, SLOT(tilesListClicked(QTreeWidgetItem*, int)));
}

/*
 * Pre-condiciones: Crea un boton "Delete" y le asigna un manejador.
 * Crea un boton "Save" y la asigna un manejador.
 * Post-condiciones: -
 * */

void Editor::setButtons() {
    QPushButton *deletePushButton = new QPushButton("Delete", this);
    rightLayout->addWidget(deletePushButton, 2);

    connect(deletePushButton, SIGNAL(released()), this,
            SLOT(handleDeleteButton()));

    QPushButton *savePushButton = new QPushButton("Save", this);
    rightLayout->addWidget(savePushButton, 2);

    connect(savePushButton, SIGNAL(released()), this,
            SLOT(handleSaveButton()));
}

/*
 * Pre-condiciones: A partir del tipo del elemento padre en la
 * lista y el nombre del elemento hijo seleccionado. Obtiene el id del
 * elemento.
 * Post-condiciones: -
 * */

int Editor::getItemId(std::string parentType, std::string name) {
    int n = parser.getItemId(parentType, name);
    if (parentType.compare("sand") == 0) {
        return n;
    } else if (parentType.compare("rock") == 0) {
        return n + ROCK_OFFSET;
    } else if (parentType.compare("dune") == 0) {
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

/*
 * Pre-condiciones: Manejador de los clicks del usuario sobre la lista
 * de posibles tiles. En caso de que el elemento clickeado sea correcto
 * lo asigna como elemento actual dentro de la clase MapScene.
 * Post-condiciones: -
 * */

void Editor::tilesListClicked(QTreeWidgetItem* item, int column) {
    if (item->childCount() == 0) {  // si no soy root
        std::string nameItem = item->text(0).toStdString();
        QTreeWidgetItem* parent = item->parent();
        std::string parentType = parent->text(0).toStdString();

        int id = getItemId(parentType, nameItem);
        std::string path = translator[id][1];
        mapScene->setCurrentItem(path, id);
    }
}

/*
 * Pre-condiciones: Manejador de los clicks del usuario sobre el botón
 * "Delete". Setea el modo de la clase MapScene como delete si ya no
 * estaba en ese modo. En caso contrario, desetea el modo delete de la
 * clase MapScene. En ambos casos muestra un mensaje informativo por
 * pantalla.
 * Post-condiciones: -
 * */

void Editor::handleDeleteButton() {
    if (!mapScene->getDeleteMode()) {
        mapScene->setDeleteMode(true);
        std::string msg("Press again to exit delete mode");
        QMessageBox::warning(this, tr("You entered delete mode"),
                             tr(msg.c_str()), QMessageBox::Close);
    } else {
        std::string msg("You exited delete mode");
        QMessageBox::warning(this, tr("Can´t delete"), tr(msg.c_str()),
                             QMessageBox::Close);
        mapScene->setDeleteMode(false);
    }
}

/*
 * Pre-condiciones: Manejador de los clicks del usuario sobre el botón
 * "Save". Si la cantidad de centros de construcción es igual a la cantidad
 * de jugadores requeridos guarda el mapa en un achivo .yaml mediante la
 * clase YamlParser. En caso contrario muestra un mensaje de error.
 * Post-condiciones: -
 * */

void Editor::handleSaveButton() {
    if (mapScene->getConstYardAmount() == map->getNPlayers()) {
        parser.saveMap(map);
        QMessageBox::information(this, tr("Saved"),
                                 tr("Mas was saved correctly"));
    } else {
        std::string msg("Map should have " +
                        std::to_string(map->getNPlayers()) +
                        " construction yards");
        QMessageBox::warning(this, tr("Can´t save"), tr(msg.c_str()),
                             QMessageBox::Close);
    }
}
