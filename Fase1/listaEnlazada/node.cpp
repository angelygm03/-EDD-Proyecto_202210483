#include "headers/node.h"

// Constructor inicializa los valores como vacíos o nulos
Node::Node() : nombres(""), apellidos(""), fechaNacimiento(""), correo(""), contrasena(""), next(nullptr) {}

// Constructor con parámetros, inicializa los valores con los datos
Node::Node(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena)
    : nombres(nombres), apellidos(apellidos), fechaNacimiento(fechaNacimiento), correo(correo), contrasena(contrasena), next(nullptr) {}

// Método para imprimir la información contenida en el nodo
void Node::print() {
    cout << "Nombres: " << nombres << endl;
    cout << "Apellidos: " << apellidos << endl;
    cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
    cout << "Correo: " << correo << endl;
    cout << "Contrasenia: " << contrasena << endl;
    cout << "Solicitudes:" << endl;
    solicitudes.print();  // Imprimir la pila de solicitudes
    cout << "-----------------------------" << endl;
}