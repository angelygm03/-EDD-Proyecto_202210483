#include "usernode.h"
#include <sstream>
#include <fstream>

UserNode::UserNode(const std::string& name) {
    userName = name;
    next = nullptr;
    neighbors = nullptr;
}

// Destructor
UserNode::~UserNode() {
    Neighbor* current = neighbors;
    while (current) {
        Neighbor* toDelete = current;
        current = current->next; // Mover al siguiente nodo
        delete toDelete; // Liberar la memoria
    }
}

// Insertar amigo en este nodo
void UserNode::insertNeighbor(const std::string& friendName) {
    // se comprueba si el vecino ya existe
    Neighbor* current = neighbors;
    while (current) {
        if (current->friendName == friendName) {
            return; // Evita duplicados
        }
        current = current->next;
    }

    // Si no existe se puede agregar
    Neighbor* newNeighbor = new Neighbor(friendName); // se crea el nuevo vecino
    newNeighbor->next = neighbors; // Agregarlo al inicio de la lista de vecinos
    neighbors = newNeighbor; // Actualizar la lista de vecinos
}

// Generar archivo de vecinos (amigos) de este nodo
void UserNode::graphNeighbors(std::ofstream &out) {
    Neighbor* aux = neighbors;
    std::stringstream origin_name;
    origin_name << "\"" << userName << "\"";
    while (aux) {
        std::stringstream destiny_name;
        destiny_name << "\"" << aux->friendName << "\"";
        out << origin_name.str() << " -> " << destiny_name.str() << " [dir = both];\n";
        aux = aux->next;
    }
}
