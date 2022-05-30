#ifndef MENUMAIN_H
#define MENUMAIN_H

#include <QDialog>

namespace Ui {
class menumain;
}

class menumain : public QDialog
{
    Q_OBJECT

public:
    explicit menumain(QWidget *parent = nullptr);
    ~menumain();

private:
    Ui::menumain *ui;
};

#endif // MENUMAIN_H
