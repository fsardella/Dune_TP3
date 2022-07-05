#include "mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <string>
#include "./ui_mainwindow.h"
#include "create_map.h"
#include "edit_map.h"

/*
 * Pre-condiciones: Constructor de la clase MainWindow (ventana inicial de qt).
 * Post-condiciones: -
 * */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QPixmap bkgr("../editor/images/new_bkg.png");
    bkgr = bkgr.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgr);
    this->setPalette(palette);
}

/*
 * Pre-condiciones: Destructor de la clase MainWindow.
 * Post-condiciones: -
 * */

MainWindow::~MainWindow() {
    delete ui;
}

/*
 * Pre-condiciones: Manejador del click del usuario sobre el botón de edición.
 * Chequea que haya mapas para editar. Si los hay cambia de ventana a una que
 * solicitará  al usuario datos referidos a edición. En caso contrario, muestra
 * un mensaje de error.
 * Post-condiciones: -
 * */

void MainWindow::on_editButton_clicked() {
    try {
        YamlParser parser;
        std::vector<std::string> maps = parser.getMaps();

        hide();

        EditMap editWindow(maps);
        editWindow.setModal(true);
        editWindow.showMaximized();
        editWindow.exec();
    } catch (std::length_error& e) {
        QMessageBox::warning(this, tr("Error"), tr("No maps available"),
                             QMessageBox::Close);
    }
}

/*
 * Pre-condiciones: Manejador del click del usuario sobre el botón de creación.
 * Cambia de ventana a una que solicitará  al usuario datos referidos
 * a la creación de mapas.
 * Post-condiciones: -
 * */

void MainWindow::on_createButton_clicked() {
    hide();
    CreateMap createWindow(NULL);
    createWindow.setModal(true);
    createWindow.showMaximized();
    createWindow.exec();
}
