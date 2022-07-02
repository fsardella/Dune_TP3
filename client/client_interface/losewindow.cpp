#include "losewindow.h"
#include "ui_losewindow.h"

LoseWindow::LoseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoseWindow) {
    ui->setupUi(this);
    QPixmap bkgnd("../client/client_interface/images/loseScreen.jpg");
    bkgnd = bkgnd.scaled(width(), height(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

LoseWindow::~LoseWindow() {
    delete ui;
}
