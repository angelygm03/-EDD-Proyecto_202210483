#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "nodebst.h"
using namespace std;

class BinarySearchTree {
private:

    NodeBST* insertar(NodeBST* node, string fecha, string correo, string contenido, string hora);
    void inorder(NodeBST* node) const;
    void generarDOT(NodeBST* node, std::ofstream& archivo) const;

public:
    NodeBST* root;
    BinarySearchTree();  // Constructor
    void insertarPublicacion(string fecha, string correo, string contenido, string hora);
    void mostrarPublicacionesEnOrden() const;
    string graficarArbol(const string& filename);
    void preorder(NodeBST* node) const;
    void postorder(NodeBST* node) const;
    void mostrarPublicacionesEnPreOrden() const;
    void mostrarPublicacionesEnPostOrden() const;
};

#endif // BINARYSEARCHTREE_H
