#ifndef CREATEGAMEWINDOW_H
#define CREATEGAMEWINDOW_H

#include <QDialog>

namespace Ui {
class CreateGameWindow;
}

class CreateGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGameWindow(QWidget *parent = nullptr);
    ~CreateGameWindow();

private slots:
    void on_createGameButton_clicked();

private:
    Ui::CreateGameWindow *ui;
};

#endif // CREATEGAMEWINDOW_H
