#include "joingamewindow.h"
#include "ui_joingamewindow.h"

JoinGameWindow::JoinGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinGameWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

JoinGameWindow::~JoinGameWindow()
{
    delete ui;
}

void JoinGameWindow::on_pushButton_clicked()
{
    this->close();
}

