/********************************************************************************
** Form generated from reading UI file 'joingamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINGAMEWINDOW_H
#define UI_JOINGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_JoinGameWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *titleLabel;
    QPushButton *joinGameButton;
    QListWidget *listWidget;

    void setupUi(QDialog *JoinGameWindow)
    {
        if (JoinGameWindow->objectName().isEmpty())
            JoinGameWindow->setObjectName(QString::fromUtf8("JoinGameWindow"));
        JoinGameWindow->resize(628, 700);
        gridLayout = new QGridLayout(JoinGameWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        titleLabel = new QLabel(JoinGameWindow);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMaximumSize(QSize(16777215, 100));
        titleLabel->setStyleSheet(QString::fromUtf8("font: 36pt \"Sarai\";"));

        gridLayout->addWidget(titleLabel, 1, 0, 1, 1);

        joinGameButton = new QPushButton(JoinGameWindow);
        joinGameButton->setObjectName(QString::fromUtf8("joinGameButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(joinGameButton->sizePolicy().hasHeightForWidth());
        joinGameButton->setSizePolicy(sizePolicy);
        joinGameButton->setMaximumSize(QSize(200, 80));
        QFont font;
        font.setFamily(QString::fromUtf8("Sarai"));
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        joinGameButton->setFont(font);
        joinGameButton->setCursor(QCursor(Qt::PointingHandCursor));
        joinGameButton->setLayoutDirection(Qt::RightToLeft);
        joinGameButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(136, 138, 133);"));
        joinGameButton->setAutoDefault(false);

        gridLayout->addWidget(joinGameButton, 3, 0, 1, 1);

        listWidget = new QListWidget(JoinGameWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMaximumSize(QSize(16777215, 400));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sarai"));
        font1.setPointSize(22);
        font1.setBold(true);
        listWidget->setFont(font1);
        listWidget->setMouseTracking(false);
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));

        gridLayout->addWidget(listWidget, 2, 0, 1, 1);


        retranslateUi(JoinGameWindow);

        QMetaObject::connectSlotsByName(JoinGameWindow);
    } // setupUi

    void retranslateUi(QDialog *JoinGameWindow)
    {
        JoinGameWindow->setWindowTitle(QApplication::translate("JoinGameWindow", "Game Election", nullptr));
        titleLabel->setText(QApplication::translate("JoinGameWindow", "<html><head/><body><p><span style=\" font-weight:700;\">GAMES LIST</span></p></body></html>", nullptr));
        joinGameButton->setText(QApplication::translate("JoinGameWindow", "JOIN GAME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoinGameWindow: public Ui_JoinGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINGAMEWINDOW_H
