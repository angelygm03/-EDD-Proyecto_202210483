#ifndef NODE_H
#define NODE_H

#include <string>
#include "stack.h"
#include "solicitudlist.h"
#include "friendlist.h"
#include "adjacencylist.h"
#include "binarysearchtree.h"

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
    AdjacencyList* adjacencyList; // Grafo de amigos
    BinarySearchTree* publicaciones; //árbol de publicaciones

    // Constructor para inicializar el nodo
    Node(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena);

    // Destructor para liberar memoria
    ~Node();
};

#endif
