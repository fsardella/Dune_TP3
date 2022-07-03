/********************************************************************************
** Form generated from reading UI file 'waitingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITINGWINDOW_H
#define UI_WAITINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_WaitingWindow
{
public:
    QFormLayout *formLayout;
    QLabel *label;

    void setupUi(QDialog *WaitingWindow)
    {
        if (WaitingWindow->objectName().isEmpty())
            WaitingWindow->setObjectName(QString::fromUtf8("WaitingWindow"));
        WaitingWindow->resize(1300, 700);
        formLayout = new QFormLayout(WaitingWindow);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(WaitingWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        retranslateUi(WaitingWindow);

        QMetaObject::connectSlotsByName(WaitingWindow);
    } // setupUi

    void retranslateUi(QDialog *WaitingWindow)
    {
        WaitingWindow->setWindowTitle(QApplication::translate("WaitingWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("WaitingWindow", "Waiting to start the game...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaitingWindow: public Ui_WaitingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITINGWINDOW_H
