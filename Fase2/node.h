#ifndef NODE_H
#define NODE_H

#include <string>
#include "stack.h"
#include "solicitudlist.h"
#include "friendlist.h"
using namespace std;

class Node {
public:
    string nombres;
    string apellidos;
    string fechaNacimiento;
    string correo;
    string contrasena;
    int factor;
    Node* left;
    Node* right;
    Stack solicitudes; //pila de solicitudes recibidas
    SolicitudList solicitudListEnviadas; //lista de solicitudes enviadas
    FriendList friends; //lista de amigos

    // Constructor para inicializar el nodo
    Node(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena);

    // Destructor para liberar memoria
    ~Node();
};

#endif
