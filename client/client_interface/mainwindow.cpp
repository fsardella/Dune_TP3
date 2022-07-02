#include "mainwindow.h"
#include <QMessageBox>
#include <string>
#include "./ui_mainwindow.h"
#include "choosehouse.h"
#include "./ui_choosehouse.h"
#include "../client_client.h"

#define PATH_MAIN "../client/client_interface/images/Dune.png"

/*
Pre: Constructor de la primer ventana que se abre al iniciar qt. 
En ella se selecciona el port, ip y nombre del jugador.
Post: Todos los atributos están inicializados.
*/

MainWindow::MainWindow(QWidget *parent, Client* client)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    newClient = client;
    ui->setupUi(this);
    QPixmap bkgnd(PATH_MAIN);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

/*
Pre: Destructor de la primer ventana que se abre al iniciar qt. 
En ella se selecciona el port, ip y nombre del jugador.
Post: -
*/

MainWindow::~MainWindow() {
    delete ui;
}

/*
Pre: Seleccionador de la opción continuar.
Post: -
*/

void MainWindow::on_continueButton_clicked() {
    std::string ip = ui->ipLineEdit->text().toStdString();
    std::string port = ui->portLineEdit->text().toStdString();
    std::string name = ui->nameLineEdit->text().toStdString();
    if (ip == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("IP field is empty."),
                             QMessageBox::Close);
        return;
    }
    if (port == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("PORT field is empty."),
                             QMessageBox::Close);
        return;
    }
    if (name == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("NAME field is empty."),
                             QMessageBox::Close);
        return;
    }
    try {
        // conecto el socket con los datos del IP y PORT.
        // A conectarlo si no estan ok alguno de los dos datos,
        // va a ser catcheado por std exception indicando que hubo un
        // error al conectarse al servidor.
        newClient->setConnection(ip.c_str(), port.c_str());
        newClient->chooseName(name);
        newClient->sendUserName();
        ChooseHouse chooseHouseWindow(NULL, newClient);
        chooseHouseWindow.setModal(true);
        this->close();
        chooseHouseWindow.showMaximized();
        chooseHouseWindow.exec();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("Error trying to connect to server."),
                             QMessageBox::Close);
        return;
    }
}

