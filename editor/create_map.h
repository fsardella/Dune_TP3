#ifndef CREATE_MAP_H
#define CREATE_MAP_H

#include <QDialog>
#include "map.h"
#include "yaml_parser.h"

namespace Ui {
class create_map;
}

class CreateMap : public QDialog {
    Q_OBJECT

 public:
    explicit CreateMap(QWidget *parent = nullptr);
    ~CreateMap();

 private slots:
    bool checkName();
    bool checkWidth();
    bool checkHeight();
    bool checkNPlayers();
    void on_pushButton_clicked();

 private:
    Ui::create_map *ui;
    Map map;
    YamlParser parser;
};

#endif  // CREATE_MAP_H
