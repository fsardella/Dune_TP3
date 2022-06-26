#include "maingame.h"
#include "ui_maingame.h"
#include "creategamewindow.h"
#include "joingamewindow.h"

#include <iostream>

MainGame::MainGame(QWidget *parent, Client* client):
    QDialog(parent),
    ui(new Ui::MainGame)
{
    newClient = client;
    ui->setupUi(this);
<<<<<<< HEAD
    QPixmap bkgnd("../client_interface/images/DuneMainGameWindow.png");
=======
    QPixmap bkgnd("../client/client_interface/images/DuneMainGameWindow.png");
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

MainGame::~MainGame()
{
    delete ui;
}

void MainGame::on_createGameButton_clicked()
{
    this->close();
    CreateGameWindow createGameWindow(NULL, newClient);
    createGameWindow.setModal(true);
    createGameWindow.showMaximized();
    createGameWindow.exec();
}


void MainGame::on_joinGameButton_clicked()
{
    this->close();
    JoinGameWindow joinGameWindow(NULL, newClient);
    joinGameWindow.setModal(true);
    joinGameWindow.showMaximized();
    joinGameWindow.exec();
}

