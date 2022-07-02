#ifndef CREATEGAMEWINDOW_H
#define CREATEGAMEWINDOW_H

#include <QDialog>
#include "../client_client.h"
#include "waitingWindow.h"

namespace Ui {
class CreateGameWindow;
}

class CreateGameWindow : public QDialog {
    Q_OBJECT

 public:
    explicit CreateGameWindow(QWidget *parent, Client* client);
    ~CreateGameWindow();

 private slots:
    void on_createGameButton_clicked();
    void showWaitingWindow();

 private:
    Client* newClient;
    Ui::CreateGameWindow *ui;
};

#endif  // CREATEGAMEWINDOW_H
