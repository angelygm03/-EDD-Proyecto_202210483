#ifndef USERWINDOW_H
#define USERWINDOW_H

#include "avltree.h"
#include <QTableWidget>
#include <QMainWindow>
#include <QPushButton>
#include "doublelist.h"
#include <QGraphicsScene>
#include "binarysearchtree.h"
#include "arbolb.h"

namespace Ui {
class Userwindow;
}

class Userwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Userwindow(QWidget *parent, AVLTree *usuariosAVL, Node *usuarioActual, DoubleList* publicacionesList, BinarySearchTree *bst, ArbolB* comentariosTree);
    ~Userwindow();
    void populateSolicitudesTable();
    void populateUsuariosNoAmigos();
    void graficarPublicacionesConAmigos();
    void populatePublicacionesList();
    void populateSolicitudesEnviadasTable();
    void imprimirNodosBST(NodeBST* node);
    void mostrarTop3Fechas();
    void contarPublicacionesPorFecha(Node* usuario, std::map<std::string, int>& conteoFechas);
    void contarPublicacionesPorFechaNodo(NodeBST* nodo, std::map<std::string, int>& conteoFechas);
    void imprimirFechasBST(NodeBST* nodo);
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

    void on_pushButton_7_reportes_clicked();

    void on_pushButton_3_recorridoAplicar_clicked();

    void on_pushButton_AplicarFecha_clicked();

    void on_pushButton_4_Comments_clicked();

    void on_pushButton_2_eliminar_clicked();

    void on_pushButton_6_verArbol_clicked();

private:
    Ui::Userwindow *ui;
    AVLTree* usuariosAVL;
    BinarySearchTree* bst;
    Stack *pilaSolicitudes;
    Node* usuarioActual;  // Usuario actual que ha iniciado sesión
    DoubleList* publicaciones;
    ArbolB* comentariosTree;
    QString imagenPath;
    NodeBST* buscarNodoPorFecha(NodeBST* node, const std::string& fecha);
    void mostrarPublicacionesEnListWidget(NodeBST* node);
    void mostrarPublicacionesDelUsuario(const std::string& usuarioCorreo);
    void mostrarPublicacionesPorFecha(NodeBST* nodo, const std::string& userEmail);
};

#endif // USERWINDOW_H
