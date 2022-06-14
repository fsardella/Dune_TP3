#include "waitingWindow.h"
#include "ui_waitingWindow.h"

WaitingWindow::WaitingWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    ui(new Ui::WaitingWindow),
    newClient(client)
{
    ui->setupUi(this);
    QPixmap bkgnd("../client_interface/images/waitingScreen.jpg");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    wait();
}

WaitingWindow::~WaitingWindow()
{
    delete ui;
}

void WaitingWindow::wait() {
    // newClient->recvStartGame();
    // this->close();
}
