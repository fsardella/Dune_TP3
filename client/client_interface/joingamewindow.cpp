#include "joingamewindow.h"
#include "ui_joingamewindow.h"
#include <QMessageBox>

#include <iostream>

JoinGameWindow::JoinGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::JoinGameWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("../client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(), 700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    std::list <std::string>list;
    newClient->sendListGamesOperation();
    newClient->recvListOfGames(list);
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

void JoinGameWindow::showWaitingWindow()
{
    this->close();
    WaitingWindow waitingWindow(NULL, this->newClient);
    waitingWindow.setModal(true);
    waitingWindow.showMaximized();
    waitingWindow.exec();
    waitingWindow.wait();
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
    int result = newClient->recvOperationResult();
    this->showWaitingWindow();
}

