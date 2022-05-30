#include "choosehouse.h"
#include "ui_choosehouse.h"
#include "maingame.h"
#include "ui_maingame.h"

ChooseHouse::ChooseHouse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseHouse)
{
    ui->setupUi(this);
}

ChooseHouse::~ChooseHouse()
{
    delete ui;
}

void ChooseHouse::show_MainGameWindow()
{
    this->hide();
    MainGame mainGameWindow;
    mainGameWindow.setModal(true);
    mainGameWindow.showMaximized();
    mainGameWindow.exec();
}

void ChooseHouse::on_harkonnenButton_clicked()
{
    show_MainGameWindow();
}

void ChooseHouse::on_atreidesButton_clicked()
{
    show_MainGameWindow();
}

void ChooseHouse::on_ordosButton_clicked()
{
    show_MainGameWindow();
}

