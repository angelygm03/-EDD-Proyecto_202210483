#ifndef USERWINDOW_H
#define USERWINDOW_H

#include "avltree.h"
#include <QTableWidget>
#include <QMainWindow>
#include <QPushButton>
#include "doublelist.h"
#include <QGraphicsScene>

namespace Ui {
class Userwindow;
}

class Userwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Userwindow(QWidget *parent, AVLTree *usuariosAVL, Node *usuarioActual, DoubleList* publicacionesList);
    ~Userwindow();
    void populateSolicitudesTable();
    void populateUsuariosNoAmigos();

private slots:
    // Funciones para manejar los eventos de la interfaz
    void on_pushButton_2_buscar_clicked();

    // Funciones para aceptar o eliminar solicitudes
    void aceptarSolicitud();
    void eliminarSolicitud();
    void on_pushButton_clicked();

    void on_pushButton_2_agregar_clicked();

    void on_pushButton_2_publicar_clicked();

    void on_pushButton_abrirImg_clicked();

private:
    Ui::Userwindow *ui;
    AVLTree* usuariosAVL;
    Stack *pilaSolicitudes;
    Node* usuarioActual;  // Usuario actual que ha iniciado sesión
    DoubleList* publicaciones;
    QString imagenPath;
};

#endif // USERWINDOW_H
