#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/Dune.png");
    //pixmap = pixmap.scaled(widWidth, widHeight, Qt::KeepAspectRatioByExpanding);
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QObject::connect(ui->continueButton, &QPushButton::clicked, this, &QMainWindow::close);
    QObject::connect(ui->btn, &QPushButton::clicked, this, &QMainWindow::close); //quiero que el usuario aprete este boton y 
                                                                            //se termine todo el programa, que no se muesten las otras ventanas. 
}

MainWindow::~MainWindow()
{
    delete ui;
}
