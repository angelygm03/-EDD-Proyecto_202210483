#include "nodebst.h"

NodeBST::NodeBST(string fecha) {
    this->fecha = fecha;
    this->left = nullptr;
    this->right = nullptr;
    this->publicaciones = FechaList();
}

