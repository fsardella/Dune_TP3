#include "create_map.h"
#include <vector>
#include <string>
#include "ui_create_map.h"
#include "editor.h"

#define MIN_WIDTH 22
#define MIN_HEIGHT 21
#define MAX_WIDTH 110
#define MAX_HEIGHT 80
#define MAX_PLAYERS 5

/*
 * Pre-condiciones: Constructor de la clase CreateMap (ventana de qt para la
 * obtención de datos referidos a la creación de un nuevo mapa).
 * Post-condiciones: -
 * */

CreateMap::CreateMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_map) {
    ui->setupUi(this);

    QPixmap bkgr("../editor/images/wallpaper.jpg");
    bkgr = bkgr.scaled(this->size(), Qt::KeepAspectRatioByExpanding);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgr);
    this->setPalette(palette);
}

/*
 * Pre-condiciones: Destructor de la clase CreateMap
 * Post-condiciones: -
 * */

CreateMap::~CreateMap() {
    delete ui;
}

/*
 * Pre-condiciones: Chequea que el nombre del mapa ingresado por el usuario
 * no este vacio y que no sea un nombre de mapa ya existente.
 * Post-condiciones: Devuelve true si el nombre es correcto, false en caso
 * contrario. En caso de que sea inválido setea un mensaje de error.
 * */

bool CreateMap::checkName() {
    QString name = ui->mapName->text();
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
                    ui->mapIncorrect->setText(
                        "This name is already associated with a map");
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

/*
 * Pre-condiciones: Chequea que el ancho del mapa ingresado por el usuario
 * no este vacio y que se encuentre dentro de los rangos válidos establecidos.
 * Post-condiciones: Devuelve true si el ancho es correcto, false en caso
 * contrario. Si era inválido setea un mensaje de error.
 * */

bool CreateMap::checkWidth() {
    QString width = ui->mapWidth->text();
    if (width.isEmpty()) {
        ui->widthIncorrect->setText("No width was entered");
        return false;
    }
    if (map.getWidth() == 0) {
        int inputWidth = width.toInt();
        if (inputWidth == 0) {
            ui->widthIncorrect->setText(
                "Width was not an integer or it was zero");
            return false;
        }
        if (inputWidth > MAX_WIDTH || inputWidth < MIN_WIDTH) {
            ui->widthIncorrect->setText(QString("Width should be between " +
                                                QString::number(MIN_WIDTH) +
                                                " and " +
                                                QString::number(MAX_WIDTH)));
            return false;
        }
        map.setWidth(inputWidth);
    }
    ui->widthIncorrect->clear();
    return true;
}

/*
 * Pre-condiciones: Chequea que el largo del mapa ingresado por el usuario
 * no este vacio y que se encuentre dentro de los rangos válidos establecidos.
 * Post-condiciones: Devuelve true si el largo es correcto, false en caso
 * contrario. Si era inválido setea un mensaje de error.
 * */

bool CreateMap::checkHeight() {
    QString height = ui->mapHeight->text();
    if (height.isEmpty()) {
        ui->heightIncorrect->setText("No height was entered");
        return false;
    }
    if (map.getHeight() == 0) {
        int inputHeight = height.toInt();
        if (inputHeight == 0) {
            ui->heightIncorrect->setText(
                "Height was not an integer or it was zero");
            return false;
        }
        if (inputHeight > MAX_HEIGHT || inputHeight < MIN_HEIGHT) {
            ui->heightIncorrect->setText(QString("Height should be between " +
                                                 QString::number(MIN_HEIGHT) +
                                                 " and " +
                                                 QString::number(MAX_HEIGHT)));
            return false;
        }
        map.setHeight(inputHeight);
    }
    ui->heightIncorrect->clear();
    return true;
}

/*
 * Pre-condiciones: Chequea que la cantidad de jugadores requeridos para
 * la partida que ingresa el usuario no sea nulo y que se encuentre dentro
 * de los rangos válidos establecidos.
 * Post-condiciones: Devuelve true si la cantidad es correcta, false en caso
 * contrario. Si era inválida setea un mensaje de error.
 * */

bool CreateMap::checkNPlayers() {
    QString n = ui->mapNPlayers->text();
    if (n.isEmpty()) {
        ui->nroIncorrect->setText("The number of players was not entered");
        return false;
    }
    if (map.getNPlayers() == 0) {
        int inputN = n.toInt();
        if (inputN == 0) {
            ui->nroIncorrect->setText(
                "Number of players was not an integer or it was zero");
            return false;
        }
        if (inputN > MAX_PLAYERS) {
            ui->nroIncorrect->setText(QString(
                "Number of players maximum is %1").arg(MAX_PLAYERS));
            return false;
        }
        map.setNPlayers(inputN);
    }
    ui->nroIncorrect->clear();
    return true;
}

/*
 * Pre-condiciones: Función asociada al click del botón. Chequea que los
 * parámetros ingresados por el usuario sean válidos. En caso satisfactorio
 * invisibiliza esta ventana y crea una nueva encargada de la edición.
 * Post-condiciones: -
 * */

void CreateMap::on_pushButton_clicked() {
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
