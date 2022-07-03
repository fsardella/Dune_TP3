/********************************************************************************
** Form generated from reading UI file 'creategamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGAMEWINDOW_H
#define UI_CREATEGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateGameWindow
{
public:
    QFormLayout *formLayout;
    QLabel *titleLabel;
    QLabel *gameNameLabel;
    QLineEdit *gameNameLineEdit;
    QPushButton *createGameButton;
    QListWidget *listWidget;

    void setupUi(QDialog *CreateGameWindow)
    {
        if (CreateGameWindow->objectName().isEmpty())
            CreateGameWindow->setObjectName(QString::fromUtf8("CreateGameWindow"));
        CreateGameWindow->resize(625, 700);
        formLayout = new QFormLayout(CreateGameWindow);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        titleLabel = new QLabel(CreateGameWindow);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMaximumSize(QSize(16777215, 500));
        QFont font;
        font.setFamily(QString::fromUtf8("Sarai"));
        font.setPointSize(36);
        font.setBold(false);
        font.setItalic(false);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("font: 36pt \"Sarai\";"));

        formLayout->setWidget(0, QFormLayout::LabelRole, titleLabel);

        gameNameLabel = new QLabel(CreateGameWindow);
        gameNameLabel->setObjectName(QString::fromUtf8("gameNameLabel"));
        gameNameLabel->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Sarai"));
        font1.setPointSize(30);
        font1.setBold(false);
        font1.setItalic(false);
        gameNameLabel->setFont(font1);
        gameNameLabel->setLayoutDirection(Qt::RightToLeft);
        gameNameLabel->setStyleSheet(QString::fromUtf8("font: 30pt \"Sarai\";"));

        formLayout->setWidget(2, QFormLayout::LabelRole, gameNameLabel);

        gameNameLineEdit = new QLineEdit(CreateGameWindow);
        gameNameLineEdit->setObjectName(QString::fromUtf8("gameNameLineEdit"));
        gameNameLineEdit->setMaximumSize(QSize(16777215, 900));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Sarai"));
        font2.setPointSize(24);
        font2.setBold(true);
        gameNameLineEdit->setFont(font2);
        gameNameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, gameNameLineEdit);

        createGameButton = new QPushButton(CreateGameWindow);
        createGameButton->setObjectName(QString::fromUtf8("createGameButton"));
        createGameButton->setMaximumSize(QSize(300, 200));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Sarai"));
        font3.setPointSize(18);
        font3.setBold(false);
        font3.setItalic(false);
        createGameButton->setFont(font3);
        createGameButton->setCursor(QCursor(Qt::PointingHandCursor));
        createGameButton->setLayoutDirection(Qt::RightToLeft);
        createGameButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"background-color: rgb(136, 138, 133);"));

        formLayout->setWidget(4, QFormLayout::LabelRole, createGameButton);

        listWidget = new QListWidget(CreateGameWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Sarai"));
        font4.setPointSize(22);
        font4.setBold(true);
        listWidget->setFont(font4);
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, listWidget);


        retranslateUi(CreateGameWindow);

        QMetaObject::connectSlotsByName(CreateGameWindow);
    } // setupUi

    void retranslateUi(QDialog *CreateGameWindow)
    {
        CreateGameWindow->setWindowTitle(QApplication::translate("CreateGameWindow", "Map Election", nullptr));
        titleLabel->setText(QApplication::translate("CreateGameWindow", "CHOOSE A MAP", nullptr));
        gameNameLabel->setText(QApplication::translate("CreateGameWindow", "GAME NAME", nullptr));
#ifndef QT_NO_WHATSTHIS
        createGameButton->setWhatsThis(QApplication::translate("CreateGameWindow", "<html><head/><body><p>CREATE GAME</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        createGameButton->setText(QApplication::translate("CreateGameWindow", "CREATE GAME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateGameWindow: public Ui_CreateGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGAMEWINDOW_H
