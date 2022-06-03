#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../client_client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, Client* client);
    ~MainWindow();

private slots:
    void on_continueButton_clicked();

private:
    Client* newClient;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
