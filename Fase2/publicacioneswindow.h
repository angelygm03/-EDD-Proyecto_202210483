#ifndef PUBLICACIONESWINDOW_H
#define PUBLICACIONESWINDOW_H
#include "doublelist.h"
#include <QMainWindow>

namespace Ui {
class Publicarwindow;
}

class Publicarwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Publicarwindow(QWidget *parent = nullptr, const string &usuarioCorreo = "");
    ~Publicarwindow();
    void setPublicacionesList(DoubleList *list);

private slots:
    void on_pushButton_2_crearPost_clicked();

private:
    Ui::Publicarwindow *ui;
    DoubleList* publicacionesList;
    std::string usuarioCorreo;
};

#endif // PUBLICACIONESWINDOW_H
