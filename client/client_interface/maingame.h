#ifndef MAINGAME_H
#define MAINGAME_H

#include <QDialog>
#include "../client_client.h"

namespace Ui {
class MainGame;
}

class MainGame : public QDialog
{
    Q_OBJECT

public:
    explicit MainGame(QWidget *parent, Client* client);
    ~MainGame();

private slots:
    void on_createGameButton_clicked();
    void on_joinGameButton_clicked();

private:
    Client* newClient;
    Ui::MainGame *ui;
};

#endif // MAINGAME_H
