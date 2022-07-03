/********************************************************************************
** Form generated from reading UI file 'losewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOSEWINDOW_H
#define UI_LOSEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_LoseWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QDialog *LoseWindow)
    {
        if (LoseWindow->objectName().isEmpty())
            LoseWindow->setObjectName(QString::fromUtf8("LoseWindow"));
        LoseWindow->resize(1300, 700);
        gridLayout = new QGridLayout(LoseWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(LoseWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(1300, 700));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(LoseWindow);

        QMetaObject::connectSlotsByName(LoseWindow);
    } // setupUi

    void retranslateUi(QDialog *LoseWindow)
    {
        LoseWindow->setWindowTitle(QApplication::translate("LoseWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("LoseWindow", "You lose the game...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoseWindow: public Ui_LoseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOSEWINDOW_H
