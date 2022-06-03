#ifndef JOINGAMEWINDOW_H
#define JOINGAMEWINDOW_H

#include <QDialog>
#include "../client_client.h"

namespace Ui {
class JoinGameWindow;
}

class JoinGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit JoinGameWindow(QWidget *parent, Client* client);
    ~JoinGameWindow();

private slots:

    void on_joinGameButton_clicked();

private:
    Client* newClient;
    Ui::JoinGameWindow *ui;
};

#endif // JOINGAMEWINDOW_H
