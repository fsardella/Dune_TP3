#include "mainwindow.h"
#include "map.h"
#include "yaml_parser.h"

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    a.exec();

//    printf("volvi\n");
//    std::cout << "name " << map.getName() << std::endl;
//    std::cout << "width " << map.getWidth() << std::endl;
//    std::cout << "height " << map.getHeight() << std::endl;
//    std::cout << "Nplayers " << map.getNPlayers() << std::endl;

    return 0;
}
