#include "creategamewindow.h"
#include "ui_creategamewindow.h"
#include <QMessageBox>

CreateGameWindow::CreateGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    ui(new Ui::CreateGameWindow)
{
    newClient = client;
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    std::list <std::string> list;
    newClient->sendListMapsOperation();
    newClient->recvListOfMaps(&list);
    list.push_back("Mapa 1"); //esto ya no iria si cargo anteriormente la lista con lo que manda el server.
    list.push_back("Mapa 2");
    list.push_back("Mapa 3");
    int size = list.size();
    for(int i = 0 ; i < size ; i++) {
        QString str = QString::fromStdString(list.back());
        this->ui->listWidget->addItem(str);
        list.pop_back();
    }
}

CreateGameWindow::~CreateGameWindow()
{
    delete ui;
}

void CreateGameWindow::on_createGameButton_clicked()
{
    if (!(ui->listWidget->currentItem())) {
        QMessageBox::warning(this, tr("Configuration error"),
                                 tr(" You have to choose a map!"),
                                 QMessageBox::Close);
        return;
    }
    else if(ui->gameNameLineEdit->text().toStdString() == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr(" You have to write a game name!"),
                             QMessageBox::Close);
        return;
    }
    newClient->chooseGameName(ui->gameNameLineEdit->text().toStdString());
    newClient->chooseMapName(this->ui->listWidget->currentItem()->text().toStdString());
    newClient->sendCreateGameOperation();
    this->close();
}
