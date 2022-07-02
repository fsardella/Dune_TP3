#include "creategamewindow.h"
#include <QMessageBox>
#include <list>
#include <string>
#include "../GameWaiter.h"
#include "ui_creategamewindow.h"

CreateGameWindow::CreateGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::CreateGameWindow) {
    ui->setupUi(this);
    QPixmap bkgnd("../client/client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(), 700, Qt::KeepAspectRatioByExpanding);
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

CreateGameWindow::~CreateGameWindow() {
    delete ui;
}

void CreateGameWindow::showWaitingWindow() {
    this->close();
    WaitingWindow waitingWindow(NULL, this->newClient);
    waitingWindow.setModal(true);
    waitingWindow.showMaximized();
    GameWaiter waiter(waitingWindow);
    waitingWindow.exec();
    waiter.join();
}

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
