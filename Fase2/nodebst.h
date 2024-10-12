#ifndef NODEBST_H
#define NODEBST_H

#include <string>
#include "fechalist.h"
using namespace std;

class NodeBST {
public:
    string fecha;  // Clave para el nodo del BST
    FechaList publicaciones;  // Lista de publicaciones para esa fecha

    NodeBST* left;
    NodeBST* right;

    NodeBST(string fecha);  // Constructor
};

#endif // NODEBST_H
