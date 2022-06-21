#include "waitingWindow.h"
#include "ui_waitingWindow.h"

#include <iostream>

WaitingWindow::WaitingWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::WaitingWindow)
{
    std::cout << "abri la waiting window\n";
    ui->setupUi(this);
    QPixmap bkgnd("../client_interface/images/waitingScreen.jpg");
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
    std::cout << "entre al wait\n";
    int res = newClient->recvStartGame();
    std::cout << "recibo " << res << std::endl;
    if (res == 5) {
        this->close();
    }
}
