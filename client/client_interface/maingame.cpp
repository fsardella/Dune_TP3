#include "maingame.h"
#include "ui_maingame.h"
#include "creategamewindow.h"
#include "joingamewindow.h"

MainGame::MainGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainGame)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/DuneMainGameWindow.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainGame::~MainGame()
{
    delete ui;
}



void MainGame::on_createGameButton_clicked()
{
    this->close();
    CreateGameWindow createGameWindow;
    createGameWindow.setModal(true);
    createGameWindow.showMaximized();
    createGameWindow.exec();
}


void MainGame::on_joinGameButton_clicked()
{
    this->close();
    JoinGameWindow joinGameWindow;
    joinGameWindow.setModal(true);
    joinGameWindow.showMaximized();
    joinGameWindow.exec();
}

