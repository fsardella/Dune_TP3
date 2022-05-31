#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "choosehouse.h"
#include "./ui_choosehouse.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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
        //info.socket.connect(ip.c_str(), port.c_str());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("Error trying to connect to server."),
                             QMessageBox::Close);
        return;
    }

    ChooseHouse chooseHouseWindow; //le paso info para que se guarde la info de la casa que elige
    chooseHouseWindow.setModal(true);
    this->close();
    chooseHouseWindow.showMaximized();
    chooseHouseWindow.exec();
}

