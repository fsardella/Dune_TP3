/********************************************************************************
** Form generated from reading UI file 'maingame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGAME_H
#define UI_MAINGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGame
{
public:
    QStatusBar *statusbar;
    QGridLayout *gridLayout;
    QPushButton *createGameButton;
    QPushButton *joinGameButton;
    QWidget *centralwidget;

    void setupUi(QDialog *MainGame)
    {
        if (MainGame->objectName().isEmpty())
            MainGame->setObjectName(QString::fromUtf8("MainGame"));
        MainGame->resize(800, 600);
        statusbar = new QStatusBar(MainGame);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 22));
        gridLayout = new QGridLayout(MainGame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        createGameButton = new QPushButton(MainGame);
        createGameButton->setObjectName(QString::fromUtf8("createGameButton"));
        createGameButton->setMaximumSize(QSize(16777215, 80));
        QFont font;
        font.setFamily(QString::fromUtf8("Sarai"));
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        createGameButton->setFont(font);
        createGameButton->setCursor(QCursor(Qt::PointingHandCursor));
        createGameButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"background-color: rgb(85, 87, 83);"));
        createGameButton->setAutoDefault(false);

        gridLayout->addWidget(createGameButton, 1, 0, 1, 1);

        joinGameButton = new QPushButton(MainGame);
        joinGameButton->setObjectName(QString::fromUtf8("joinGameButton"));
        joinGameButton->setMaximumSize(QSize(16777215, 80));
        joinGameButton->setCursor(QCursor(Qt::PointingHandCursor));
        joinGameButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"background-color: rgb(85, 87, 83);"));
        joinGameButton->setAutoDefault(false);

        gridLayout->addWidget(joinGameButton, 1, 1, 1, 1);

        centralwidget = new QWidget(MainGame);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMaximumSize(QSize(16777215, 300));

        gridLayout->addWidget(centralwidget, 0, 0, 1, 2);


        retranslateUi(MainGame);

        QMetaObject::connectSlotsByName(MainGame);
    } // setupUi

    void retranslateUi(QDialog *MainGame)
    {
        MainGame->setWindowTitle(QApplication::translate("MainGame", "Mode Election", nullptr));
        createGameButton->setText(QApplication::translate("MainGame", "CREATE GAME", nullptr));
        joinGameButton->setText(QApplication::translate("MainGame", "JOIN GAME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGame: public Ui_MainGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGAME_H
