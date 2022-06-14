#include "waitingWindow.h"
#include "ui_waitingWindow.h"

WaitingWindow::WaitingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("../client_interface/images/waitingScreen.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

WaitingWindow::~WaitingWindow()
{
    delete ui;
}
