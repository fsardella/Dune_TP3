/********************************************************************************
** Form generated from reading UI file 'edit_map.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_MAP_H
#define UI_EDIT_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_edit_map
{
public:
    QLabel *label;
    QPushButton *continueBotton;
    QListWidget *mapsList;
    QLabel *noMapSelected;

    void setupUi(QDialog *edit_map)
    {
        if (edit_map->objectName().isEmpty())
            edit_map->setObjectName(QString::fromUtf8("edit_map"));
        edit_map->resize(1300, 700);
        label = new QLabel(edit_map);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 110, 221, 51));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(190, 190, 190, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("URW Bookman"));
        font.setPointSize(29);
        font.setBold(true);
        label->setFont(font);
        continueBotton = new QPushButton(edit_map);
        continueBotton->setObjectName(QString::fromUtf8("continueBotton"));
        continueBotton->setGeometry(QRect(1100, 630, 121, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("URW Bookman"));
        font1.setPointSize(12);
        font1.setBold(true);
        continueBotton->setFont(font1);
        mapsList = new QListWidget(edit_map);
        mapsList->setObjectName(QString::fromUtf8("mapsList"));
        mapsList->setGeometry(QRect(200, 190, 901, 341));
        QFont font2;
        font2.setFamily(QString::fromUtf8("URW Bookman"));
        font2.setPointSize(20);
        font2.setBold(true);
        mapsList->setFont(font2);
        noMapSelected = new QLabel(edit_map);
        noMapSelected->setObjectName(QString::fromUtf8("noMapSelected"));
        noMapSelected->setGeometry(QRect(210, 540, 551, 31));
        QPalette palette1;
        QBrush brush2(QColor(254, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        QBrush brush3(QColor(224, 27, 36, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush3);
        QBrush brush4(QColor(231, 231, 231, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush4);
        QBrush brush5(QColor(255, 255, 255, 127));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush4);
        noMapSelected->setPalette(palette1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("URW Bookman"));
        font3.setPointSize(14);
        font3.setBold(true);
        noMapSelected->setFont(font3);

        retranslateUi(edit_map);

        QMetaObject::connectSlotsByName(edit_map);
    } // setupUi

    void retranslateUi(QDialog *edit_map)
    {
        edit_map->setWindowTitle(QCoreApplication::translate("edit_map", "Dune", nullptr));
        label->setText(QCoreApplication::translate("edit_map", "Map list", nullptr));
        continueBotton->setText(QCoreApplication::translate("edit_map", "Continue", nullptr));
        noMapSelected->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class edit_map: public Ui_edit_map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_MAP_H
