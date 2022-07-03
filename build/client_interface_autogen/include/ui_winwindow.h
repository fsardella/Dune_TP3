/********************************************************************************
** Form generated from reading UI file 'winwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINWINDOW_H
#define UI_WINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_WinWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *winLabel;

    void setupUi(QDialog *WinWindow)
    {
        if (WinWindow->objectName().isEmpty())
            WinWindow->setObjectName(QString::fromUtf8("WinWindow"));
        WinWindow->resize(1300, 700);
        gridLayout = new QGridLayout(WinWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        winLabel = new QLabel(WinWindow);
        winLabel->setObjectName(QString::fromUtf8("winLabel"));
        winLabel->setMaximumSize(QSize(1300, 700));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        winLabel->setFont(font);
        winLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        gridLayout->addWidget(winLabel, 0, 0, 1, 1);


        retranslateUi(WinWindow);

        QMetaObject::connectSlotsByName(WinWindow);
    } // setupUi

    void retranslateUi(QDialog *WinWindow)
    {
        WinWindow->setWindowTitle(QApplication::translate("WinWindow", "Dialog", nullptr));
        winLabel->setText(QApplication::translate("WinWindow", "You win the game!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinWindow: public Ui_WinWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINWINDOW_H
