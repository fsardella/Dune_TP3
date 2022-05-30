#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "choosehouse.h"
#include "./ui_choosehouse.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/Dune.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_continueButton_clicked()
{
    this->hide();
    ChooseHouse chooseHouseWindow;
    chooseHouseWindow.setModal(true);
    chooseHouseWindow.showMaximized();
    chooseHouseWindow.exec();
}

