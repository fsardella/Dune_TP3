#include "maingame.h"
#include "ui_maingame.h"
#include "creategamewindow.h"
#include "joingamewindow.h"

#define PATH_MAIN_GAME "../client/client_interface/images/DuneMainGameWindow.png"

/*
Pre: Constructor de la ventana donde se selecciona el crear o el unirse en el
juego.
Post: Todos los atributos están inicializados.
*/

MainGame::MainGame(QWidget *parent, Client* client):
    QDialog(parent),
    ui(new Ui::MainGame) {
    newClient = client;
    ui->setupUi(this);
    QPixmap bkgnd(PATH_MAIN_GAME);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

/*
Pre: Destructor de la ventana donde se selecciona el crear o el unirse en el
juego.
Post: -
*/

MainGame::~MainGame() {
    delete ui;
}

/*
Pre: Seleccionador de la opción crear una partida.
Post: -
*/

void MainGame::on_createGameButton_clicked() {
    this->close();
    CreateGameWindow createGameWindow(NULL, newClient);
    createGameWindow.setModal(true);
    createGameWindow.showMaximized();
    createGameWindow.exec();
}

/*
Pre: Seleccionador de la opción unirse a la partida.
Post: -
*/

void MainGame::on_joinGameButton_clicked() {
    this->close();
    JoinGameWindow joinGameWindow(NULL, newClient);
    joinGameWindow.setModal(true);
    joinGameWindow.showMaximized();
    joinGameWindow.exec();
}
