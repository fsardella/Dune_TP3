#ifndef MAINGAME_H
#define MAINGAME_H

#include <QDialog>

namespace Ui {
class MainGame;
}

class MainGame : public QDialog
{
    Q_OBJECT

public:
    explicit MainGame(QWidget *parent = nullptr);
    ~MainGame();

private slots:
    void on_createGameButton_clicked();
    void on_joinGameButton_clicked();

private:
    Ui::MainGame *ui;
};

#endif // MAINGAME_H
