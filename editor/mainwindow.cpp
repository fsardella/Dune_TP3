#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "create_map.h"
#include "edit_map.h"

#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgr("../editor/images/new_bkg.png");
    bkgr = bkgr.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgr);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_editButton_clicked()
{
    try {
        YamlParser parser;
        std::vector<std::string> maps = parser.getMaps();

        hide();

        EditMap editWindow(maps);
        editWindow.setModal(true);
        editWindow.showMaximized();
        editWindow.exec();
    } catch(std::length_error& e) {
        QMessageBox::warning(this, tr("Error"), tr("No maps available"), QMessageBox::Close);
    }
}


void MainWindow::on_createButton_clicked()
{
    hide();
    CreateMap createWindow(NULL);
    createWindow.setModal(true);
    createWindow.showMaximized();
    createWindow.exec();
}

