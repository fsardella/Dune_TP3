#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "choosehouse.h"
#include "./ui_choosehouse.h"
#include <QMessageBox>
#include "../client_client.h"

MainWindow::MainWindow(QWidget *parent, Client* client)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    newClient = client;
    ui->setupUi(this);
    QPixmap bkgnd("../client/client_interface/images/Dune.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_continueButton_clicked()
{
    std::string ip = ui->ipLineEdit->text().toStdString();
    std::string port = ui->portLineEdit->text().toStdString();
    std::string name = ui->nameLineEdit->text().toStdString();
    if(ip == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("IP field is empty."),
                             QMessageBox::Close);
        return;
    }
    if(port == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("PORT field is empty."),
                             QMessageBox::Close);
        return;
    }
    if(name == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("NAME field is empty."),
                             QMessageBox::Close);
        return;
    }
    try {
        //conecto el socket con los datos del IP y PORT. A conectarlo si no estan ok alguno de los dos datos,
        //va a ser catcheado por std exception indicando que hubo un error al conectarse al servidor.
        newClient->setConnection(ip.c_str(), port.c_str()); // por ahora lo comento para que no me de error al no tener el server
        newClient->chooseName(name);
        newClient->sendUserName();
        ChooseHouse chooseHouseWindow(NULL, newClient); //le paso al cliente para que se guarde la info de la casa que elige
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

