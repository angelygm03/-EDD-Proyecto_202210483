#include "adjacencylist.h"
#include <iostream>
using namespace std;

AdjacencyList::AdjacencyList() {
    head = nullptr;
}

// Destructor
AdjacencyList::~AdjacencyList() {
    UserNode* current = head;
    while (current) {
        UserNode* toDelete = current;
        current = current->next; // Mover al siguiente nodo
        delete toDelete; // Liberar memoria del nodo UserNode y sus neighbors
    }
}

// Insertar un nuevo nodo (usuario)
void AdjacencyList::insert(const string& userName) {
    UserNode* newNode = new UserNode(userName);
    if (!head) {
        head = newNode;
    } else {
        UserNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Crear una conexión (amistad) entre dos usuarios
void AdjacencyList::createConnection(const string& userName1, const string& userName2) {
    UserNode* current = head;
    while (current) {
        if (current->userName == userName1) {
            current->insertNeighbor(userName2);
            break;
        }
        current = current->next;
    }

    current = head; // Reset el puntero para buscar en la cabeza nuevamente
    while (current) {
        if (current->userName == userName2) {
            current->insertNeighbor(userName1);
            break;
        }
        current = current->next;
    }
}

// Generar gráfico del grafo
void AdjacencyList::graph(const string &filename) {
    ofstream out(filename + ".dot");
    if (!out) {
        cerr << "Error al crear el archivo dot\n";
        return;
    }

    out << "digraph g {\n";
    out << "rankdir=LR;\n";

    UserNode* current = head;
    while (current) {
        out << "\"" << current->userName << "\" [label=\"" << current->userName << "\"];\n";
        current->graphNeighbors(out);
        current = current->next;
    }

    out << "}\n";
    out.close();

    // Comando para generar la imagen (Graphviz debe estar instalado)
    string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    int result = system(command.c_str());

    if (result != 0) {
        cout << "Ocurrió un error al generar la imagen.\n";
    } else {
        cout << "La imagen fue generada exitosamente.\n";
    }
}
