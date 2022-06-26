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
    QLabel *titlelabel;
    QLabel *label_ip;
    QVBoxLayout *vLayaout_ip;
    QLineEdit *ipLineEdit;
    QLabel *label_port;
    QVBoxLayout *vLayaout_port;
    QLineEdit *portLineEdit;
    QLabel *label_name;
    QVBoxLayout *vLayaout_name;
    QLineEdit *nameLineEdit;
    QVBoxLayout *vLayout_continue;
    QPushButton *continueButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMaximumSize(QSize(800, 600));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        titlelabel = new QLabel(centralwidget);
        titlelabel->setObjectName(QString::fromUtf8("titlelabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sarai"));
        font.setBold(false);
        titlelabel->setFont(font);
        titlelabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(titlelabel, 0, 0, 1, 1);

        label_ip = new QLabel(centralwidget);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sarai"));
        font1.setBold(true);
        label_ip->setFont(font1);
        label_ip->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_ip, 1, 0, 1, 1);

        vLayaout_ip = new QVBoxLayout();
        vLayaout_ip->setObjectName(QString::fromUtf8("vLayaout_ip"));
        ipLineEdit = new QLineEdit(centralwidget);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Vemana2000"));
        font2.setPointSize(18);
        font2.setBold(true);
        ipLineEdit->setFont(font2);
        ipLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));
        ipLineEdit->setAlignment(Qt::AlignCenter);

        vLayaout_ip->addWidget(ipLineEdit);


        gridLayout->addLayout(vLayaout_ip, 2, 0, 1, 1);

        label_port = new QLabel(centralwidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        label_port->setFont(font1);
        label_port->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_port, 3, 0, 1, 1);

        vLayaout_port = new QVBoxLayout();
        vLayaout_port->setObjectName(QString::fromUtf8("vLayaout_port"));
        portLineEdit = new QLineEdit(centralwidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setFont(font2);
        portLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));
        portLineEdit->setAlignment(Qt::AlignCenter);

        vLayaout_port->addWidget(portLineEdit);


        gridLayout->addLayout(vLayaout_port, 4, 0, 1, 1);

        label_name = new QLabel(centralwidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setFont(font1);
        label_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_name, 5, 0, 1, 1);

        vLayaout_name = new QVBoxLayout();
        vLayaout_name->setObjectName(QString::fromUtf8("vLayaout_name"));
        nameLineEdit = new QLineEdit(centralwidget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setFont(font2);
        nameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));
        nameLineEdit->setAlignment(Qt::AlignCenter);

        vLayaout_name->addWidget(nameLineEdit);


        gridLayout->addLayout(vLayaout_name, 6, 0, 1, 1);

        vLayout_continue = new QVBoxLayout();
        vLayout_continue->setSpacing(6);
        vLayout_continue->setObjectName(QString::fromUtf8("vLayout_continue"));
        vLayout_continue->setContentsMargins(0, -1, -1, 0);
        continueButton = new QPushButton(centralwidget);
        continueButton->setObjectName(QString::fromUtf8("continueButton"));
        continueButton->setMinimumSize(QSize(200, 60));
        continueButton->setMaximumSize(QSize(80, 16777215));
        continueButton->setBaseSize(QSize(0, 0));
        QFont font3;
        font3.setFamily(QString::fromUtf8("URW Gothic"));
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setItalic(false);
        continueButton->setFont(font3);
        continueButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"font: 63 11pt \"URW Gothic\";\n"
"background-color: rgb(136, 138, 133);"));

        vLayout_continue->addWidget(continueButton, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        gridLayout->addLayout(vLayout_continue, 7, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DUNE 2000", nullptr));
        titlelabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:72pt; font-weight:600; color:#000000;\">DUNE 2000</span></p></body></html>", nullptr));
        label_ip->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600; color:#000000;\">IP</span></p></body></html>", nullptr));
        label_port->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600; color:#000000;\">PORT</span></p></body></html>", nullptr));
        label_name->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600; color:#000000;\">USER NAME</span></p></body></html>", nullptr));
        continueButton->setText(QApplication::translate("MainWindow", "CONTINUE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
