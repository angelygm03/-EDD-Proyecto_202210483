#ifndef AVLTREE_H
#define AVLTREE_H
#include "node.h"
#include <fstream>
#include <QTableWidget>

#define LEFT_HEAVY -1
#define BALANCED 0
#define RIGHT_HEAVY 1

class AVLTree {
private:

    Node* insert(Node* root, string nombres, string apellidos, string fechaNacimiento,
                 string correo, string contrasena, bool increase);
    Node* l_rotation(Node* n, Node* n1);
    Node* r_rotation(Node* n, Node* n1);
    Node* lr_rotation(Node* n, Node* n1);
    Node* rl_rotation(Node* n, Node* n1);
    void graph(Node *root, std::ofstream &content);
    Node* buscarPorCorreo(Node* root, const string& correo);
    Node* eliminarPorCorreo(Node* root, const string& correo, bool& decrease);

public:
    Node* root;
    AVLTree();
    void insert(string nombres, string apellidos, string fechaNacimiento,
                string correo, string contrasena);
    void graph();
    Node* buscarPorCorreo(const string& correo);
    bool verificarCredenciales(const string& correo, const string& contrasena);
    void preorden(Node* node);
    void inorden(Node* node);
    void postorden(Node* node);
    void preorden(Node* node, QTableWidget* table, int& row);
    void inorden(Node* node, QTableWidget* table, int& row);
    void postorden(Node* node, QTableWidget* table, int& row);
    void eliminarPorCorreo(const string& correo);
    void agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
};
#endif // AVLTREE_H
