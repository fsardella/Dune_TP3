/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_port;
    QVBoxLayout *vLayout_continue;
    QPushButton *continueButton;
    QLabel *label;
    QVBoxLayout *vLayaout_ip;
    QLineEdit *lineEdit;
    QVBoxLayout *vLayaout_port;
    QLineEdit *lineEdit_2;
    QLabel *label_ip;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(680, 362);
        MainWindow->setMaximumSize(QSize(800, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(193, 125, 17);\n"
"border-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_port = new QLabel(centralwidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sarai"));
        label_port->setFont(font);
        label_port->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_port, 3, 0, 1, 1);

        vLayout_continue = new QVBoxLayout();
        vLayout_continue->setObjectName(QString::fromUtf8("vLayout_continue"));
        continueButton = new QPushButton(centralwidget);
        continueButton->setObjectName(QString::fromUtf8("continueButton"));
        continueButton->setFont(font);
        continueButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));

        vLayout_continue->addWidget(continueButton, 0, Qt::AlignVCenter);


        gridLayout->addLayout(vLayout_continue, 5, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sarai"));
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        vLayaout_ip = new QVBoxLayout();
        vLayaout_ip->setObjectName(QString::fromUtf8("vLayaout_ip"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setAlignment(Qt::AlignCenter);

        vLayaout_ip->addWidget(lineEdit);


        gridLayout->addLayout(vLayaout_ip, 2, 0, 1, 1);

        vLayaout_port = new QVBoxLayout();
        vLayaout_port->setObjectName(QString::fromUtf8("vLayaout_port"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setAlignment(Qt::AlignCenter);

        vLayaout_port->addWidget(lineEdit_2);


        gridLayout->addLayout(vLayaout_port, 4, 0, 1, 1);

        label_ip = new QLabel(centralwidget);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setFont(font);
        label_ip->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_ip, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 680, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_port->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600; color:#000000;\">PORT</span></p></body></html>", nullptr));
        continueButton->setText(QApplication::translate("MainWindow", "CONTINUE", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:72pt; font-weight:600; color:#000000;\">DUNE 2000</span></p></body></html>", nullptr));
        label_ip->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600; color:#000000;\">IP</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
