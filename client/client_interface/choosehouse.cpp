#include "choosehouse.h"
#include <qt5/QtWidgets/qwidget.h>
#include "ui_choosehouse.h"
#include "maingame.h"
#include "ui_maingame.h"

/*
Pre: Constructor de ventana para seleccionar la casa.
Post: Todos los atributos están inicializados.
*/

ChooseHouse::ChooseHouse(QWidget *parent, Client* client) :
    QDialog(parent),
    client(client),
    ui(new Ui::ChooseHouse) {
    ui->setupUi(this);
}

/*
Pre: Destructor de ventana para seleccionar la casa.
Post: -
*/

ChooseHouse::~ChooseHouse() {
    delete ui;
}

/*
Pre: Visualizador de ventana principal para elegir crear una partida 
o unirse a una partida.
Post: -
*/

void ChooseHouse::show_MainGameWindow() {
    this->close();
    MainGame mainGameWindow(NULL, this->client);
    mainGameWindow.setModal(true);
    mainGameWindow.showMaximized();
    mainGameWindow.exec();
}

/*
Pre: Seleccionador de casa harkonnen.
Post: -
*/

void ChooseHouse::on_harkonnenButton_clicked() {
    client->chooseNumberHouse(HOUSE_HARKONNEN);
    show_MainGameWindow();
}

/*
Pre: Seleccionador de casa atreides.
Post: -
*/

void ChooseHouse::on_atreidesButton_clicked() {
    client->chooseNumberHouse(HOUSE_ATREIDES);
    show_MainGameWindow();
}

/*
Pre: Seleccionador de casa ordos.
Post: -
*/

void ChooseHouse::on_ordosButton_clicked() {
    client->chooseNumberHouse(HOUSE_ORDOS);
    show_MainGameWindow();
}
