#ifndef MATRIX_H
#define MATRIX_H

#include "matrixNode.h"
#include "../listaEnlazada/headers/node.h" 
#include <iostream>
#include <set>
#include <string>

class Matrix {
private:

public:
    Matrix();
    ~Matrix();
    MatrixNode* head;
    void insertarRelacion(Node* usuario1, Node* usuario2);
    bool sonAmigos(Node* usuario1, Node* usuario2);
    void printMatrix() const;
    void generateDotFile(const std::string& filename) const;
    void top5MenosAmigos() const;
    std::set<std::string> getAmigos(const std::string& correoUsuario) const;

};

#endif
