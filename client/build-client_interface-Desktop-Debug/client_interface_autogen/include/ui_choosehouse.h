/********************************************************************************
** Form generated from reading UI file 'choosehouse.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEHOUSE_H
#define UI_CHOOSEHOUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooseHouse
{
public:
    QGridLayout *gridLayout;
    QLabel *titleLabel;
    QLabel *harkonnenLabel;
    QLabel *atreidesLabel;
    QLabel *ordosLabel;
    QPushButton *harkonnenButton;
    QPushButton *atreidesButton;
    QPushButton *ordosButton;

    void setupUi(QDialog *ChooseHouse)
    {
        if (ChooseHouse->objectName().isEmpty())
            ChooseHouse->setObjectName(QString::fromUtf8("ChooseHouse"));
        ChooseHouse->resize(727, 410);
        ChooseHouse->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        gridLayout = new QGridLayout(ChooseHouse);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        titleLabel = new QLabel(ChooseHouse);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMaximumSize(QSize(16777215, 100));
        titleLabel->setStyleSheet(QString::fromUtf8("font: 36pt \"Sarai\";"));

        gridLayout->addWidget(titleLabel, 0, 0, 1, 3);

        harkonnenLabel = new QLabel(ChooseHouse);
        harkonnenLabel->setObjectName(QString::fromUtf8("harkonnenLabel"));
        harkonnenLabel->setMaximumSize(QSize(16777215, 300));
        harkonnenLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/d2kharkonnen.png);"));

        gridLayout->addWidget(harkonnenLabel, 1, 0, 1, 1);

        atreidesLabel = new QLabel(ChooseHouse);
        atreidesLabel->setObjectName(QString::fromUtf8("atreidesLabel"));
        atreidesLabel->setMaximumSize(QSize(16777215, 300));
        atreidesLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/d2katreides.png);"));

        gridLayout->addWidget(atreidesLabel, 1, 1, 1, 1);

        ordosLabel = new QLabel(ChooseHouse);
        ordosLabel->setObjectName(QString::fromUtf8("ordosLabel"));
        ordosLabel->setMaximumSize(QSize(16777215, 300));
        ordosLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/d2kordos.png);"));

        gridLayout->addWidget(ordosLabel, 1, 2, 1, 1);

        harkonnenButton = new QPushButton(ChooseHouse);
        harkonnenButton->setObjectName(QString::fromUtf8("harkonnenButton"));
        harkonnenButton->setMaximumSize(QSize(500, 16777215));
        harkonnenButton->setCursor(QCursor(Qt::PointingHandCursor));
        harkonnenButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"color: rgb(239, 41, 41);\n"
"selection-background-color: rgb(46, 52, 54);\n"
"background-color: rgb(136, 138, 133);"));
        harkonnenButton->setAutoDefault(false);

        gridLayout->addWidget(harkonnenButton, 2, 0, 1, 1);

        atreidesButton = new QPushButton(ChooseHouse);
        atreidesButton->setObjectName(QString::fromUtf8("atreidesButton"));
        atreidesButton->setMaximumSize(QSize(500, 400));
        atreidesButton->setCursor(QCursor(Qt::PointingHandCursor));
        atreidesButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"color: rgb(52, 101, 164);\n"
"selection-background-color: rgb(46, 52, 54);\n"
"background-color: rgb(136, 138, 133);"));
        atreidesButton->setAutoDefault(false);

        gridLayout->addWidget(atreidesButton, 2, 1, 1, 1);

        ordosButton = new QPushButton(ChooseHouse);
        ordosButton->setObjectName(QString::fromUtf8("ordosButton"));
        ordosButton->setMaximumSize(QSize(500, 400));
        ordosButton->setCursor(QCursor(Qt::PointingHandCursor));
        ordosButton->setStyleSheet(QString::fromUtf8("font: 18pt \"Sarai\";\n"
"color: rgb(78, 154, 6);\n"
"selection-background-color: rgb(46, 52, 54);\n"
"background-color: rgb(136, 138, 133);"));
        ordosButton->setAutoDefault(false);

        gridLayout->addWidget(ordosButton, 2, 2, 1, 1);

        QWidget::setTabOrder(ordosButton, harkonnenButton);
        QWidget::setTabOrder(harkonnenButton, atreidesButton);

        retranslateUi(ChooseHouse);

        QMetaObject::connectSlotsByName(ChooseHouse);
    } // setupUi

    void retranslateUi(QDialog *ChooseHouse)
    {
        ChooseHouse->setWindowTitle(QApplication::translate("ChooseHouse", "House Election", nullptr));
        titleLabel->setText(QApplication::translate("ChooseHouse", "<html><head/><body><p><span style=\" font-size:48pt; color:#d3d7cf;\">CHOOSE YOUR HOUSE</span></p></body></html>", nullptr));
        harkonnenLabel->setText(QString());
        atreidesLabel->setText(QString());
        ordosLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        harkonnenButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        harkonnenButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        harkonnenButton->setText(QApplication::translate("ChooseHouse", "Harkonnen", nullptr));
        atreidesButton->setText(QApplication::translate("ChooseHouse", "Atreides", nullptr));
        ordosButton->setText(QApplication::translate("ChooseHouse", "Ordos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseHouse: public Ui_ChooseHouse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEHOUSE_H
