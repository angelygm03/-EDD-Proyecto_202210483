#include "node.h"

// Constructor para inicializar el nodo
Node::Node(string nombres, string apellidos, string fechaNacimiento,
           string correo, string contrasena) {
    this->nombres = nombres;
    this->apellidos = apellidos;
    this->fechaNacimiento = fechaNacimiento;
    this->correo = correo;
    this->contrasena = contrasena;

    left = nullptr;
    right = nullptr;
    factor = 0;
}
// Destructor para liberar la memoria de los nodos hijos
Node::~Node() {
    delete left;
    delete right;
}
