#include "creategamewindow.h"
#include <QMessageBox>
#include <list>
#include <string>
#include "../GameWaiter.h"
#include "ui_creategamewindow.h"

#define PATH_CREATE_GAME "../client/client_interface/images/DuneCreateGame.png"

/*
Pre: Constructor de ventana para crear el juego.
Post: Todos los atributos están inicializados.
*/

CreateGameWindow::CreateGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::CreateGameWindow) {
    ui->setupUi(this);
    QPixmap bkgnd(PATH_CREATE_GAME);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    std::list<std::string> list;
    // newClient->sendListMapsOperation();
    newClient->sendCreateGameOperation();
    newClient->recvListOfMaps(list);
    int size = list.size();
    for (int i = 0; i < size; i++) {
        QString str = QString::fromStdString(list.back());
        this->ui->listWidget->addItem(str);
        list.pop_back();
    }
}

/*
Pre: Destructor de ventana para crear el juego.
Post: -
*/

CreateGameWindow::~CreateGameWindow() {
    delete ui;
}

/*
Pre: Visualizador de ventana de espera.
Post: -
*/

void CreateGameWindow::showWaitingWindow() {
    this->close();
    WaitingWindow waitingWindow(NULL, this->newClient);
    waitingWindow.setModal(true);
    waitingWindow.showMaximized();
    GameWaiter waiter(waitingWindow);
    waitingWindow.exec();
    waiter.join();
}

/*
Pre: Seleccionador de crear juego.
Post: -
*/

void CreateGameWindow::on_createGameButton_clicked() {
    if (!(ui->listWidget->currentItem())) {
        QMessageBox::warning(this, tr("Configuration error"),
                                 tr(" You have to choose a map!"),
                                 QMessageBox::Close);
        return;
    } else if (ui->gameNameLineEdit->text().toStdString() == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr(" You have to write a game name!"),
                             QMessageBox::Close);
        return;
    }
    newClient->chooseGameName(ui->gameNameLineEdit->text().toStdString());
    newClient->chooseMapName(this->ui->listWidget->currentItem()->text().
                             toStdString());
    newClient->sendCreateGameInfo();
    int result = newClient->recvOperationResult();
    if (result == 0) {
        newClient->setReadyToRun();
    }
    this->showWaitingWindow();
}
