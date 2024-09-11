#ifndef MATRIXNODE_H
#define MATRIXNODE_H

#include <string>

class MatrixNode {
public:
    std::string correo;
    MatrixNode* right;
    MatrixNode* down;

    MatrixNode(const std::string& correo);
};

#endif // MATRIXNODE_H
