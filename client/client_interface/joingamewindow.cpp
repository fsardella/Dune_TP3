#include "joingamewindow.h"
#include "ui_joingamewindow.h"
#include <QMessageBox>

JoinGameWindow::JoinGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    ui(new Ui::JoinGameWindow)
{
    newClient = client;
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    std::list <std::string> list;
    newClient->sendListGamesOperation();
    newClient->recvListOfGames(&list);
    list.push_back("Tres amigos"); //esto ya no iria si cargo anteriormente la lista con lo que manda el server.
    list.push_back("Dune version");
    list.push_back("Dos amigos");
    int size = list.size();
    for(int i = 0 ; i < size ; i++) {
        QString str = QString::fromStdString(list.back());
        this->ui->listWidget->addItem(str);
        list.pop_back();
    }
}

JoinGameWindow::~JoinGameWindow()
{
    delete ui;
}

void JoinGameWindow::on_joinGameButton_clicked()
{
    if (!(this->ui->listWidget->currentItem())) {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr(" You have to choose a game!"),
                             QMessageBox::Close);
        return;
    }
    newClient->chooseGameName(this->ui->listWidget->currentItem()->text().toStdString());
    newClient->sendJoinGameOperation();
    this->close();
}

