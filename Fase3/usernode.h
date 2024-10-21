#ifndef USERNODE_H
#define USERNODE_H

#include <string>
#include "neighbor.h"

class UserNode {
public:
    std::string userName; // Nombre del usuario
    UserNode* next; // Siguiente nodo en la lista
    Neighbor* neighbors; // Lista de amigos

    UserNode(const std::string& name);
    ~UserNode();
    void insertNeighbor(const std::string& friendName);
    void graphNeighbors(std::ofstream &out); // Método para generar el archivo de vecinos
};

#endif // USERNODE_H
