#ifndef STACKNODE_H
#define STACKNODE_H

#include <string>
using namespace std;

// Clase que representa un nodo en la pila de solicitudes
class StackNode {
public:
    string emisor;
    string receptor;
    string estado;
    StackNode* next;

    // Constructor del nodo
    StackNode(string emisor, string receptor, string estado);
};

#endif
