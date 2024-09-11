#include "matrixNode.h"

MatrixNode::MatrixNode(const std::string& correo)
    : correo(correo), right(nullptr), down(nullptr) {}
