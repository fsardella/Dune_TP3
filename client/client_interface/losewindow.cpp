#include "losewindow.h"
#include "ui_losewindow.h"

#define PATH_LOSE "../client/client_interface/images/loseScreen.jpg"
/*
Pre: Constructor de ventana para cuando se pierde en el juego.
Post: Todos los atributos están inicializados.
*/

LoseWindow::LoseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoseWindow) {
    ui->setupUi(this);
    QPixmap bkgnd(PATH_LOSE);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

/*
Pre: Destructor de ventana para cuando se pierde en el juego.
Post: -
*/

LoseWindow::~LoseWindow() {
    delete ui;
}
