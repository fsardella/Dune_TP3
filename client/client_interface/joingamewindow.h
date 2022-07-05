#ifndef JOINGAMEWINDOW_H
#define JOINGAMEWINDOW_H

#include <QDialog>
#include "../client_client.h"
#include "waitingWindow.h"

namespace Ui {
class JoinGameWindow;
}

class JoinGameWindow : public QDialog {
    Q_OBJECT

 public:
    explicit JoinGameWindow(QWidget *parent, Client* client);
    ~JoinGameWindow();

 private slots:

    void on_joinGameButton_clicked();
    void showWaitingWindow();

 private:
    Client* newClient;
    Ui::JoinGameWindow *ui;
};

#endif  // JOINGAMEWINDOW_H
