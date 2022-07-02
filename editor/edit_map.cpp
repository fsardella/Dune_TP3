#include "edit_map.h"
#include <vector>
#include "ui_edit_map.h"
#include "editor.h"

/*
 * Pre-condiciones: Constructor de la clase EditMap (ventana de qt para la
 * obtención de datos referidos a la edición de un mapa existente).
 * Post-condiciones: -
 * */

EditMap::EditMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_map) {
    ui->setupUi(this);
    QPixmap bkgr("../editor/images/wallpaper.jpg");
    bkgr = bkgr.scaled(this->size(), Qt::KeepAspectRatioByExpanding);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgr);
    this->setPalette(palette);
}

/*
 * Pre-condiciones: Constructor de la clase EditMap (ventana de qt para la
 * obtención de datos referidos a la edición de un mapa existente). Recibe
 * una lista con los mapas existentes para que el usuario seleccione el de
 * preferencia.
 * Post-condiciones: -
 * */

EditMap::EditMap(std::vector<std::string>& maps, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_map),
    maps(maps) {
    ui->setupUi(this);

    QPixmap bkgr("../editor/images/wallpaper.jpg");
    bkgr = bkgr.scaled(this->size(), Qt::KeepAspectRatioByExpanding);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgr);
    this->setPalette(palette);

    showList();
}

/*
 * Pre-condiciones: Constructor de la clase EditMap.
 * Post-condiciones: -
 * */

EditMap::~EditMap() {
    delete ui;
}

/*
 * Pre-condiciones: Muestra por pantalla una lista con los nombres
 * de los mapas existentes.
 * Post-condiciones: -
 * */

void EditMap::showList() {
    for (const std::string& name : maps) {
        QString mapName = QString::fromStdString(name);
        ui->mapsList->addItem(mapName);
    }
}

/*
 * Pre-condiciones: Función asociada al click del botón "continue".
 * Chequea que se haya seleccionado el nombre de un mapa existente.
 * En caso satisfactorio, invisibiliza esta ventana y crea una nueva
 * encargada de la edición. En caso contrario, setea un mensaje de error.
 * Post-condiciones: -
 * */

void EditMap::on_continueBotton_clicked() {
    if (ui->mapsList->currentItem()) {
        ui->noMapSelected->clear();

        std::string name = ui->mapsList->currentItem()->text().toStdString();

        map.setIsNotNew();
        map.setName(name);

        hide();
        Editor editor(&map);
        editor.setModal(true);
        editor.showMaximized();
        editor.exec();
    } else {
        ui->noMapSelected->setText("No map was selected");
    }
}
