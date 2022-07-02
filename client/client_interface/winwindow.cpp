#include "winwindow.h"
#include "ui_winwindow.h"

WinWindow::WinWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinWindow) {
    ui->setupUi(this);
    QPixmap bkgnd("../client/client_interface/images/winScreen.jpeg");
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

WinWindow::~WinWindow() {
    delete ui;
}
