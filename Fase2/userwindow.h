#ifndef USERWINDOW_H
#define USERWINDOW_H

#include "avltree.h"
#include <QTableWidget>
#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class Userwindow;
}

class Userwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Userwindow(QWidget *parent = nullptr, AVLTree *usuariosAVL = nullptr, Node *usuarioActual = nullptr);
    ~Userwindow();
    void populateSolicitudesTable();

private slots:
    // Funciones para manejar los eventos de la interfaz
    void on_pushButton_2_buscar_clicked();
    void on_actionVer_solicitudes_triggered();

    // Funciones para aceptar o eliminar solicitudes
    void aceptarSolicitud();
    void eliminarSolicitud();

    void on_pushButton_2_verSolicitudes_clicked();

    void on_pushButton_clicked();

private:
    Ui::Userwindow *ui;
    AVLTree* usuariosAVL;
    Stack *pilaSolicitudes;
    Node* usuarioActual;  // Usuario actual que ha iniciado sesión
};

#endif // USERWINDOW_H
