#include "choosehouse.h"
#include "ui_choosehouse.h"
#include "maingame.h"
#include "ui_maingame.h"
#include <qt5/QtWidgets/qwidget.h>

ChooseHouse::ChooseHouse(QWidget *parent, Client* client) :
    QDialog(parent),
    ui(new Ui::ChooseHouse), client(client)
{
    ui->setupUi(this);
}

ChooseHouse::~ChooseHouse()
{
    delete ui;
}

void ChooseHouse::show_MainGameWindow()
{
    this->close();
    MainGame mainGameWindow(this, this->client);
    mainGameWindow.setModal(true);
    mainGameWindow.showMaximized();
    mainGameWindow.exec();
}

void ChooseHouse::on_harkonnenButton_clicked()
{
    client->chooseNumberHouse(HOUSE_HARKONNEN);
    show_MainGameWindow();
}

void ChooseHouse::on_atreidesButton_clicked()
{
    client->chooseNumberHouse(HOUSE_ATREIDES);
    show_MainGameWindow();
}

void ChooseHouse::on_ordosButton_clicked()
{
    client->chooseNumberHouse(HOUSE_ORDOS);
    show_MainGameWindow();
}

