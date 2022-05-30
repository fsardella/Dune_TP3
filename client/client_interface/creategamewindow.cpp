#include "creategamewindow.h"
#include "ui_creategamewindow.h"

CreateGameWindow::CreateGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGameWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

CreateGameWindow::~CreateGameWindow()
{
    delete ui;
}
