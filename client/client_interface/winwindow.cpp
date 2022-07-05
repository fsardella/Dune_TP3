#include "winwindow.h"
#include "ui_winwindow.h"

#define PATH_WIN "../client/client_interface/images/winScreen.jpeg"

/*
Pre: Constructor de ventana para cuando se gana en el juego.
Post: Todos los atributos están inicializados.
*/

WinWindow::WinWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinWindow) {
    ui->setupUi(this);
    QPixmap bkgnd(PATH_WIN);
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

/*
Pre: Destructor de ventana para cuando se gana en el juego.
Post: -
*/

WinWindow::~WinWindow() {
    delete ui;
}
