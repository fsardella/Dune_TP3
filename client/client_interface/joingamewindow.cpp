#include "joingamewindow.h"
#include "ui_joingamewindow.h"
#include <QMessageBox>

JoinGameWindow::JoinGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    ui(new Ui::JoinGameWindow)
{
    newClient = client;
    ui->setupUi(this);
    QPixmap bkgnd("/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    std::list <QString> list; //por ahora lo hardcodeo, despues el server me lo va a pasar
    list.push_back("Tres amigos");
    list.push_back("Dune version");
    list.push_back("Dos amigos");
    for(int i = 0 ; i < 3 ; i++) {
        this->ui->listWidget->addItem(list.back());
        list.pop_back();
    }
}

JoinGameWindow::~JoinGameWindow()
{
    delete ui;
}

void JoinGameWindow::on_joinGameButton_clicked()
{
    if (!(this->ui->listWidget->currentItem())) {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr(" You have to choose a game!"),
                             QMessageBox::Close);
        return;
    }
    newClient->chooseGameName(this->ui->listWidget->currentItem()->text().toStdString());
    this->close();
}

