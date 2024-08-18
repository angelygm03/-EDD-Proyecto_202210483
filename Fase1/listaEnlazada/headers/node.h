#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "../../pila/headers/stack.h"
using namespace std;

class Node {
public:
    string nombres;
    string apellidos;
    string fechaNacimiento;
    string correo;
    string contrasena;
    Stack solicitudes;  // Pila de solicitudes
    Node* next;

    Node();
    Node(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena);

    void print();
};

#endif
