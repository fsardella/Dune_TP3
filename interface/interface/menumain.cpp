#include "menumain.h"
#include "ui_menumain.h"

menumain::menumain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menumain)
{
    ui->setupUi(this);
}

menumain::~menumain()
{
    delete ui;
}
