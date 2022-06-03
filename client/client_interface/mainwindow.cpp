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
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/Dune.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
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
    try {
        //conecto el socket con los datos del IP y PORT. A conectarlo si no estan ok alguno de los dos datos,
        //va a ser catcheado por std exception indicando que hubo un error al conectarse al servidor.
       // Client client(ip.c_str(), port.c_str());
        newClient->setProtocol(ip.c_str(), port.c_str());
        ChooseHouse chooseHouseWindow(this, newClient); //le paso al cliente para que se guarde la info de la casa que elige
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

