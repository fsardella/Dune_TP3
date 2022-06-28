#ifndef LOSEWINDOW_H
#define LOSEWINDOW_H

#include <QDialog>

namespace Ui {
class LoseWindow;
}

class LoseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoseWindow(QWidget *parent = nullptr);
    ~LoseWindow();

private:
    Ui::LoseWindow *ui;
};

#endif // LOSEWINDOW_H
