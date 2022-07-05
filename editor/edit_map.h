#ifndef EDIT_MAP_H
#define EDIT_MAP_H

#include <QDialog>
#include <vector>
#include <string>
#include "map.h"
#include "yaml_parser.h"

namespace Ui {
class edit_map;
}

class EditMap : public QDialog {
    Q_OBJECT

 public:
    explicit EditMap(QWidget *parent = nullptr);
    explicit EditMap(std::vector<std::string>& maps, QWidget *parent = nullptr);
    ~EditMap();

 private slots:
    void showList();
    void on_continueBotton_clicked();

 private:
    Ui::edit_map *ui;
    Map map;
    std::vector<std::string> maps;
};

#endif  // EDIT_MAP_H
