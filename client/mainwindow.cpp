#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    QPushButton* btn = new QPushButton("EXIT", this);
    btn->setGeometry(10, 10, 120, 30);
    QFont font;
    font.setFamily(QString::fromUtf8("Sarai"));
    btn->setFont(font);
    btn->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 138, 133);"));

    QObject::connect(ui->continueButton, &QPushButton::clicked, this, &QMainWindow::close);
    QObject::connect(btn, &QPushButton::clicked, this, &QMainWindow::close); //quiero que el usuario aprete este boton y 
                                                                            //se termine todo el programa, que no se muesten las otras ventanas. 
}

MainWindow::~MainWindow()
{
    delete ui;
}
