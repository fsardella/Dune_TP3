#include "waitingWindow.h"
#include "ui_waitingWindow.h"

#include <iostream>

WaitingWindow::WaitingWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::WaitingWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
    QPixmap bkgnd("../client_interface/images/waitingScreen.jpg");
=======
    QPixmap bkgnd("../client/client_interface/images/waitingScreen.jpg");
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

WaitingWindow::~WaitingWindow()
{
    delete ui;
}

void WaitingWindow::wait() {
    int res = newClient->recvStartGame();
    if (res == 5) {
        this->close();
    }
}
