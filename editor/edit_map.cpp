#include "edit_map.h"
#include <vector>
#include "ui_edit_map.h"
#include "editor.h"

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

EditMap::~EditMap() {
    delete ui;
}

void EditMap::showList() {
    for (const std::string& name : maps) {
        QString mapName = QString::fromStdString(name);
        ui->mapsList->addItem(mapName);
    }
}

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
