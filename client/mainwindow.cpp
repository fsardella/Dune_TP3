#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* btn = new QPushButton("Salir", this);
    btn->setGeometry(10, 10, 120, 30);

    QObject::connect(ui->continueButton, &QPushButton::clicked, this, &QMainWindow::close);
    QObject::connect(btn, &QPushButton::clicked, this, &QMainWindow::close); //quiero que el usuario aprete este boton y 
                                                                            //se termine todo el programa, que no se muesten las otras ventanas. 
}

MainWindow::~MainWindow()
{
    delete ui;
}
