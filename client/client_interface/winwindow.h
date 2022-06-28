#ifndef WINWINDOW_H
#define WINWINDOW_H

#include <QDialog>

namespace Ui {
class WinWindow;
}

class WinWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WinWindow(QWidget *parent = nullptr);
    ~WinWindow();

private:
    Ui::WinWindow *ui;
};

#endif // WINWINDOW_H
