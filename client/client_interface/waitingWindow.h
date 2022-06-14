#ifndef WAITINGWINDOW_H
#define WAITINGWINDOW_H

#include <QDialog>

namespace Ui {
class WaitingWindow;
}

class WaitingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingWindow(QWidget *parent = nullptr);
    ~WaitingWindow();

private:
    Ui::WaitingWindow *ui;
};

#endif // WAITINGWINDOW_H
