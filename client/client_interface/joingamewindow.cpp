#include "joingamewindow.h"
#include <QMessageBox>
#include <list>
#include <string>
#include "../GameWaiter.h"
#include "ui_joingamewindow.h"

#define PATH_JOIN_GAME "../client/client_interface/images/DuneCreateGame.png"
/*
Pre: Constructor de ventana para unirse a un juego.
Post: Todos los atributos están inicializados.
*/

JoinGameWindow::JoinGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::JoinGameWindow) {
    ui->setupUi(this);
    QPixmap bkgnd(PATH_JOIN_GAME);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    std::list<std::string> list;
    newClient->sendListGamesOperation();
    newClient->recvListOfGames(list);
    int size = list.size();
    for (int i = 0 ; i < size ; i++) {
        QString str = QString::fromStdString(list.back());
        this->ui->listWidget->addItem(str);
        list.pop_back();
    }
}

/*
Pre: Destructor de ventana para unirse a un juego.
Post: -
*/

JoinGameWindow::~JoinGameWindow() {
    delete ui;
}

/*
Pre: Visualizador de ventana de espera.
Post: -
*/

void JoinGameWindow::showWaitingWindow() {
    this->close();
    WaitingWindow waitingWindow(NULL, this->newClient);
    waitingWindow.setModal(true);
    waitingWindow.showMaximized();
    GameWaiter waiter(waitingWindow);
    waitingWindow.exec();
    waiter.join();
}

/*
Pre: Seleccionador de unirse al juego.
Post: -
*/

void JoinGameWindow::on_joinGameButton_clicked() {
    if (!(this->ui->listWidget->currentItem())) {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr(" You have to choose a game!"),
                             QMessageBox::Close);
        return;
    }
    newClient->chooseGameName(this->ui->listWidget->currentItem()->text().
                              toStdString());
    newClient->sendJoinGameOperation();
    int result = newClient->recvOperationResult();
    if (result == 0) {
        newClient->setReadyToRun();
    }
    this->showWaitingWindow();
}

