#include <QApplication>
#include "mainwindow.h"
#include "map.h"
#include "yaml_parser.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    a.exec();

    return 0;
}
