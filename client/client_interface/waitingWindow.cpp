#include "waitingWindow.h"
#include "ui_waitingWindow.h"

#define PATH_WAITING "../client/client_interface/images/waitingScreen.jpg"
#define START_GAME_SIGNAL 5
/*
Pre: Constructor de la ventana de espera.
Post: Todos los atributos están inicializados.
*/

WaitingWindow::WaitingWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::WaitingWindow) {
    ui->setupUi(this);
    QPixmap bkgnd(PATH_WAITING);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

/*
Pre: Destructor de la ventana de espera.
Post: -
*/

WaitingWindow::~WaitingWindow() {
    delete ui;
}

/*
Pre: Se espera a que se llegue a la cantidad de jugadores requeridos para
poder cerrar la ventana de espera e iniciar el juego.
Post: -
*/

void WaitingWindow::wait() {
    int res = newClient->recvStartGame();
    if (res == START_GAME_SIGNAL) {
        this->close();
    }
}
