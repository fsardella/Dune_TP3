#ifndef WAITINGWINDOW_H
#define WAITINGWINDOW_H

#include <QDialog>
#include "../client_client.h"

namespace Ui {
class WaitingWindow;
}

class WaitingWindow : public QDialog {
    Q_OBJECT

 public:
    explicit WaitingWindow(QWidget *parent, Client* client);
    ~WaitingWindow();
    void wait();

 private:
    Client* newClient;
    Ui::WaitingWindow *ui;
};

#endif  // WAITINGWINDOW_H
