#include "creategamewindow.h"
#include "ui_creategamewindow.h"
#include <QMessageBox>

#include <iostream>

CreateGameWindow::CreateGameWindow(QWidget *parent, Client* client) :
    QDialog(parent),
    newClient(client),
    ui(new Ui::CreateGameWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("../client_interface/images/DuneCreateGame.png");
    bkgnd = bkgnd.scaled(width(),700, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    std::list<std::string> list;
    // newClient->sendListMapsOperation();
    newClient->sendCreateGameOperation();
    std::cout << "antes de recibir lista\n";
    newClient->recvListOfMaps(list);
    std::cout << "desp de recibir lista\n";
    // list.push_back("Mapa 1"); //esto ya no iria si cargo anteriormente la lista con lo que manda el server.
    // list.push_back("Mapa 2");
    // list.push_back("Mapa 3");
    int size = list.size();
    std::cout << size << std::endl;
    for(int i = 0; i < size; i++) {
        QString str = QString::fromStdString(list.back());
        this->ui->listWidget->addItem(str);
        list.pop_back();
    }
}

CreateGameWindow::~CreateGameWindow()
{
    delete ui;
}

void CreateGameWindow::showWaitingWindow()
{
    this->close();
    std::cout << "abro ventana de waiting\n";
    WaitingWindow waitingWindow(NULL, this->newClient);
    std::cout << "se creo ventana\n";
    waitingWindow.setModal(true);
    waitingWindow.showMaximized();
    waitingWindow.exec();
    std::cout << "voy a entrar al wait\n";
    waitingWindow.wait();
}

void CreateGameWindow::on_createGameButton_clicked()
{
    if (!(ui->listWidget->currentItem())) {
        QMessageBox::warning(this, tr("Configuration error"),
                                 tr(" You have to choose a map!"),
                                 QMessageBox::Close);
        return;
    }
    else if(ui->gameNameLineEdit->text().toStdString() == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr(" You have to write a game name!"),
                             QMessageBox::Close);
        return;
    }
    newClient->chooseGameName(ui->gameNameLineEdit->text().toStdString());
    newClient->chooseMapName(this->ui->listWidget->currentItem()->text().toStdString());
    newClient->sendCreateGameInfo();
    int result = newClient->recvOperationResult();
    std::cout << "result a create " << result << std::endl;
    // this->close();
    this->showWaitingWindow();
}
