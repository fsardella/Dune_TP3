/********************************************************************************
** Form generated from reading UI file 'create_map.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_MAP_H
#define UI_CREATE_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_create_map
{
public:
    QLabel *label;
    QLineEdit *mapName;
    QLabel *label_2;
    QLineEdit *mapWidth;
    QLabel *label_3;
    QLineEdit *mapHeight;
    QLabel *label_4;
    QLineEdit *mapNPlayers;
    QPushButton *pushButton;
    QLabel *mapIncorrect;
    QLabel *widthIncorrect;
    QLabel *heightIncorrect;
    QLabel *nroIncorrect;

    void setupUi(QDialog *create_map)
    {
        if (create_map->objectName().isEmpty())
            create_map->setObjectName(QString::fromUtf8("create_map"));
        create_map->resize(1300, 700);
        QPalette palette;
        create_map->setPalette(palette);
        label = new QLabel(create_map);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 110, 221, 41));
        QPalette palette1;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush);
        QBrush brush1(QColor(127, 127, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush1);
        QBrush brush2(QColor(170, 170, 170, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush3);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush6(QColor(0, 0, 0, 128));
        brush6.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
        label->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("URW Bookman"));
        font.setPointSize(29);
        font.setBold(true);
        label->setFont(font);
        mapName = new QLineEdit(create_map);
        mapName->setObjectName(QString::fromUtf8("mapName"));
        mapName->setGeometry(QRect(170, 170, 951, 30));
        label_2 = new QLabel(create_map);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 250, 101, 31));
        QPalette palette2;
        QBrush brush7(QColor(239, 239, 239, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush7);
        QBrush brush8(QColor(247, 247, 247, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush8);
        QBrush brush9(QColor(119, 119, 119, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush9);
        QBrush brush10(QColor(159, 159, 159, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush10);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush3);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush8);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush3);
        QBrush brush11(QColor(231, 231, 231, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        QBrush brush12(QColor(35, 35, 35, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush12);
        QBrush brush13(QColor(202, 202, 202, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        QBrush brush14(QColor(160, 160, 160, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush14);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush11);
        QBrush brush15(QColor(255, 0, 0, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush15);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush11);
        QBrush brush16(QColor(51, 51, 51, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush16);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush16);
        QBrush brush17(QColor(118, 118, 118, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush17);
        QBrush brush18(QColor(81, 81, 81, 255));
        brush18.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush18);
        QBrush brush19(QColor(0, 0, 0, 102));
        brush19.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush19);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        QBrush brush20(QColor(177, 177, 177, 255));
        brush20.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush20);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush18);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush19);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush11);
        label_2->setPalette(palette2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("URW Bookman"));
        font1.setPointSize(22);
        font1.setBold(true);
        label_2->setFont(font1);
        mapWidth = new QLineEdit(create_map);
        mapWidth->setObjectName(QString::fromUtf8("mapWidth"));
        mapWidth->setGeometry(QRect(170, 290, 951, 30));
        label_3 = new QLabel(create_map);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 360, 111, 41));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        QBrush brush21(QColor(255, 255, 255, 127));
        brush21.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush21);
        label_3->setPalette(palette3);
        label_3->setFont(font1);
        mapHeight = new QLineEdit(create_map);
        mapHeight->setObjectName(QString::fromUtf8("mapHeight"));
        mapHeight->setGeometry(QRect(170, 410, 951, 30));
        label_4 = new QLabel(create_map);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 480, 221, 51));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush21);
        label_4->setPalette(palette4);
        label_4->setFont(font1);
        mapNPlayers = new QLineEdit(create_map);
        mapNPlayers->setObjectName(QString::fromUtf8("mapNPlayers"));
        mapNPlayers->setGeometry(QRect(170, 540, 951, 30));
        pushButton = new QPushButton(create_map);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1138, 644, 121, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("URW Bookman"));
        font2.setPointSize(12);
        font2.setBold(true);
        pushButton->setFont(font2);
        mapIncorrect = new QLabel(create_map);
        mapIncorrect->setObjectName(QString::fromUtf8("mapIncorrect"));
        mapIncorrect->setGeometry(QRect(170, 200, 711, 21));
        QPalette palette5;
        QBrush brush22(QColor(224, 27, 36, 255));
        brush22.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush22);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush21);
        mapIncorrect->setPalette(palette5);
        QFont font3;
        font3.setFamily(QString::fromUtf8("URW Bookman"));
        font3.setPointSize(13);
        font3.setBold(true);
        mapIncorrect->setFont(font3);
        widthIncorrect = new QLabel(create_map);
        widthIncorrect->setObjectName(QString::fromUtf8("widthIncorrect"));
        widthIncorrect->setGeometry(QRect(170, 320, 991, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush22);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush21);
        widthIncorrect->setPalette(palette6);
        widthIncorrect->setFont(font3);
        heightIncorrect = new QLabel(create_map);
        heightIncorrect->setObjectName(QString::fromUtf8("heightIncorrect"));
        heightIncorrect->setGeometry(QRect(170, 440, 951, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush22);
        QBrush brush23(QColor(52, 52, 52, 255));
        brush23.setStyle(Qt::SolidPattern);
        palette7.setBrush(QPalette::Active, QPalette::Light, brush23);
        QBrush brush24(QColor(43, 43, 43, 255));
        brush24.setStyle(Qt::SolidPattern);
        palette7.setBrush(QPalette::Active, QPalette::Midlight, brush24);
        QBrush brush25(QColor(17, 17, 17, 255));
        brush25.setStyle(Qt::SolidPattern);
        palette7.setBrush(QPalette::Active, QPalette::Dark, brush25);
        QBrush brush26(QColor(23, 23, 23, 255));
        brush26.setStyle(Qt::SolidPattern);
        palette7.setBrush(QPalette::Active, QPalette::Mid, brush26);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush22);
        palette7.setBrush(QPalette::Active, QPalette::BrightText, brush22);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush12);
        palette7.setBrush(QPalette::Active, QPalette::Shadow, brush3);
        palette7.setBrush(QPalette::Active, QPalette::AlternateBase, brush25);
        palette7.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette7.setBrush(QPalette::Active, QPalette::ToolTipText, brush22);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette7.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette7.setBrush(QPalette::Inactive, QPalette::Mid, brush14);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::BrightText, brush15);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush11);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush16);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush16);
        palette7.setBrush(QPalette::Inactive, QPalette::Shadow, brush17);
        palette7.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush18);
        palette7.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush19);
        palette7.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush11);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush25);
        palette7.setBrush(QPalette::Disabled, QPalette::Light, brush23);
        palette7.setBrush(QPalette::Disabled, QPalette::Midlight, brush24);
        palette7.setBrush(QPalette::Disabled, QPalette::Dark, brush25);
        palette7.setBrush(QPalette::Disabled, QPalette::Mid, brush26);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush25);
        palette7.setBrush(QPalette::Disabled, QPalette::BrightText, brush22);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush25);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush12);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush12);
        palette7.setBrush(QPalette::Disabled, QPalette::Shadow, brush20);
        palette7.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush18);
        palette7.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush19);
        palette7.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush11);
        heightIncorrect->setPalette(palette7);
        heightIncorrect->setFont(font3);
        nroIncorrect = new QLabel(create_map);
        nroIncorrect->setObjectName(QString::fromUtf8("nroIncorrect"));
        nroIncorrect->setGeometry(QRect(170, 570, 681, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush22);
        palette8.setBrush(QPalette::Active, QPalette::Light, brush23);
        palette8.setBrush(QPalette::Active, QPalette::Midlight, brush24);
        palette8.setBrush(QPalette::Active, QPalette::Dark, brush25);
        palette8.setBrush(QPalette::Active, QPalette::Mid, brush26);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush22);
        palette8.setBrush(QPalette::Active, QPalette::BrightText, brush22);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush12);
        palette8.setBrush(QPalette::Active, QPalette::Shadow, brush3);
        palette8.setBrush(QPalette::Active, QPalette::AlternateBase, brush25);
        palette8.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette8.setBrush(QPalette::Active, QPalette::ToolTipText, brush22);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette8.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Midlight, brush13);
        palette8.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette8.setBrush(QPalette::Inactive, QPalette::Mid, brush14);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush11);
        palette8.setBrush(QPalette::Inactive, QPalette::BrightText, brush15);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush11);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush16);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush16);
        palette8.setBrush(QPalette::Inactive, QPalette::Shadow, brush17);
        palette8.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush18);
        palette8.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush19);
        palette8.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush11);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush25);
        palette8.setBrush(QPalette::Disabled, QPalette::Light, brush23);
        palette8.setBrush(QPalette::Disabled, QPalette::Midlight, brush24);
        palette8.setBrush(QPalette::Disabled, QPalette::Dark, brush25);
        palette8.setBrush(QPalette::Disabled, QPalette::Mid, brush26);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush25);
        palette8.setBrush(QPalette::Disabled, QPalette::BrightText, brush22);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush25);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush12);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush12);
        palette8.setBrush(QPalette::Disabled, QPalette::Shadow, brush20);
        palette8.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush18);
        palette8.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush19);
        palette8.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush11);
        nroIncorrect->setPalette(palette8);
        nroIncorrect->setFont(font3);

        retranslateUi(create_map);

        QMetaObject::connectSlotsByName(create_map);
    } // setupUi

    void retranslateUi(QDialog *create_map)
    {
        create_map->setWindowTitle(QCoreApplication::translate("create_map", "Dune", nullptr));
        label->setText(QCoreApplication::translate("create_map", "Map Name", nullptr));
        label_2->setText(QCoreApplication::translate("create_map", "Width", nullptr));
        label_3->setText(QCoreApplication::translate("create_map", "Height", nullptr));
        label_4->setText(QCoreApplication::translate("create_map", "Nro of players", nullptr));
        pushButton->setText(QCoreApplication::translate("create_map", "Continue", nullptr));
        mapIncorrect->setText(QString());
        widthIncorrect->setText(QString());
        heightIncorrect->setText(QString());
        nroIncorrect->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class create_map: public Ui_create_map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_MAP_H
