#include "create_map.h"
#include "ui_create_map.h"
#include "editor.h"

#define MIN_WIDTH 22
#define MIN_HEIGHT 21
#define MAX_WIDTH 110
#define MAX_HEIGHT 80
#define MAX_PLAYERS 10 // cambiar

CreateMap::CreateMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_map)
{
    ui->setupUi(this);

    QPixmap bkgr("/home/florencia/taller/repo_grupo/my_images/wallpaper.jpg");
    bkgr = bkgr.scaled(this->size(), Qt::KeepAspectRatioByExpanding);

    QPalette palette;
    palette.setBrush(QPalette::Background, bkgr);
    this->setPalette(palette);
}

CreateMap::~CreateMap()
{
    delete ui;
}

bool CreateMap::checkName() {
    QString name=ui->mapName->text();
    if (name.isEmpty()) {
        ui->mapIncorrect->setText("No map name was entered");
        return false;
    }
    if (map.getName().empty()) {
        std::string inputName = name.toStdString();
        try {
            std::vector<std::string> maps = parser.getMaps();
            for (std::string& mapName : maps) {
                if (mapName.compare(inputName) == 0) {
                    ui->mapIncorrect->setText("This name is already associated with a map");
                    return false;
                }
            }
            map.setName(inputName);
        } catch(std::length_error& e) {
            map.setName(inputName);
        }
    }
    ui->mapIncorrect->clear();
    return true;
}

bool CreateMap::checkWidth() {
    QString width=ui->mapWidth->text();
    if (width.isEmpty()) {
        ui->widthIncorrect->setText("No width was entered");
        return false;
    }
    if (map.getWidth() == 0) {
        int inputWidth = width.toInt();
        if (inputWidth == 0) {
            ui->widthIncorrect->setText("Width was not an integer or it was zero");
            return false;
        }
        if (inputWidth > MAX_WIDTH || inputWidth < MIN_WIDTH) {
            ui->widthIncorrect->setText(QString("Width should be between " +
                                                QString::number(MIN_WIDTH) + " and " +
                                                QString::number(MAX_WIDTH)));
            return false;
        }
        map.setWidth(inputWidth);
    }
    ui->widthIncorrect->clear();
    return true;
}

bool CreateMap::checkHeight() {
    QString height=ui->mapHeight->text();
    if (height.isEmpty()) {
        ui->heightIncorrect->setText("No height was entered");
        return false;
    }
    if (map.getHeight() == 0) {
        int inputHeight = height.toInt();
        if (inputHeight == 0) {
            ui->heightIncorrect->setText("Height was not an integer or it was zero");
            return false;
        }
        if (inputHeight > MAX_HEIGHT || inputHeight < MIN_HEIGHT) {
            ui->heightIncorrect->setText(QString("Height should be between " +
                                                 QString::number(MIN_HEIGHT) + " and " +
                                                 QString::number(MAX_HEIGHT)));
            return false;
        }
        map.setHeight(inputHeight);
    }
    ui->heightIncorrect->clear();
    return true;
}
bool CreateMap::checkNPlayers() {
    QString n=ui->mapNPlayers->text();
    if (n.isEmpty()) {
        ui->nroIncorrect->setText("The number of players was not entered");
        return false;
    }
    if (map.getNPlayers() == 0) {
        int inputN = n.toInt();
        if (inputN == 0) {
            ui->nroIncorrect->setText("Number of players was not an integer or it was zero");
            return false;
        }
        if (inputN > MAX_PLAYERS) {
            ui->nroIncorrect->setText(QString("Number of players maximum is %1").arg(MAX_PLAYERS));
            return false;
        }
        map.setNPlayers(inputN);
    }
    ui->nroIncorrect->clear();
    return true;
}


void CreateMap::on_pushButton_clicked()
{
    bool correctName = checkName();
    bool correctWidth = checkWidth();
    bool correctHeight = checkHeight();
    bool correctNPlayers = checkNPlayers();

    if (correctName && correctWidth && correctHeight && correctNPlayers) {
        hide();
        Editor editor(&map);
        editor.setModal(true);
        editor.showMaximized();
        editor.exec();
    }
}

