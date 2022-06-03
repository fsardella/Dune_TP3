#ifndef CHOOSEHOUSE_H
#define CHOOSEHOUSE_H

#include <QDialog>
#include "../client_client.h"

namespace Ui {
class ChooseHouse;
}

class ChooseHouse : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseHouse(QWidget *parent, Client* client);
    ~ChooseHouse();
    void show_MainGameWindow();

private slots:
    void on_harkonnenButton_clicked();
    void on_atreidesButton_clicked();
    void on_ordosButton_clicked();

private:
    Client* client;
    Ui::ChooseHouse *ui;
};

#endif // CHOOSEHOUSE_H
