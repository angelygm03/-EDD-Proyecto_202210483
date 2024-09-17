#ifndef CREARPUBLICACION_H
#define CREARPUBLICACION_H
#include "doublelist.h"
#include <QMainWindow>

namespace Ui {
class CrearPublicacion;
}

class CrearPublicacion : public QMainWindow
{
    Q_OBJECT

public:
    explicit CrearPublicacion(QWidget *parent = nullptr, const std::string &correoUsuario = "", DoubleList *list = nullptr);
    ~CrearPublicacion();

private slots:
    void on_plainTextEdit_contenidoPost_textChanged();

    void on_pushButton_abrirImg_clicked();

    void on_pushButton_2_postear_clicked();

private:
    Ui::CrearPublicacion *ui;
    DoubleList *publicacionesList;
    std::string usuarioCorreo;
};

#endif // CREARPUBLICACION_H
