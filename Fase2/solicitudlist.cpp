#include "solicitudlist.h"
#include <iostream>
#include <fstream>

// Constructor inicializa la cabeza de la lista como nula y el tamaño en 0
SolicitudList::SolicitudList() : head(nullptr), size(0) {}

// Método para insertar una nueva solicitud al final de la lista
void SolicitudList::insert(string emisor, string receptor, string estado) {
    SolicitudNode* newNode = new SolicitudNode(emisor, receptor, estado);

    if (head == nullptr) {
        head = newNode;
    } else {
        SolicitudNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

// Método para imprimir todas las solicitudes en la lista
void SolicitudList::print() {
    if (head == nullptr) {
        cout << "No hay solicitudes en la lista." << endl;
        return;
    }

    SolicitudNode* current = head;
    while (current != nullptr) {
        cout << "Emisor: " << current->emisor << ", Receptor: " << current->receptor << ", Estado: " << current->estado << endl;
        current = current->next;
    }
}

// Método para eliminar una solicitud de la lista
bool SolicitudList::eliminar(const string& emisor, const string& receptor) {
    if (head == nullptr) {
        return false;
    }

    if (head->emisor == emisor && head->receptor == receptor) {
        SolicitudNode* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    SolicitudNode* current = head;
    while (current->next != nullptr) {
        if (current->next->emisor == emisor && current->next->receptor == receptor) {
            SolicitudNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Método para buscar una solicitud en la lista
SolicitudNode* SolicitudList::buscar(const string& emisor, const string& receptor) {
    SolicitudNode* current = head;
    while (current != nullptr) {
        if (current->emisor == emisor && current->receptor == receptor) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Método para generar el archivo dot de las solicitudes
void SolicitudList::generateDotFile(const string& fileName) {
    ofstream file("reporteSolicitudes.dot");
    if (!file.is_open()) {
        cout << "Error al abrir el archivo para escribir el gráfico." << endl;
        return;
    }

    file << "digraph G {\n";
    file << "rankdir=LR;\n";
    file << "    node [shape=box];\n";

    SolicitudNode* current = head;
    while (current != nullptr) {
        file << "    \"" << current->receptor << "\";\n";
        current = current->next;
    }

    current = head;
    while (current != nullptr && current->next != nullptr) {
        file << "    \"" << current->receptor << "\" -> \"" << current->next->receptor << "\";\n";
        current = current->next;
    }

    file << "}\n";
    file.close();

    // Convertir el archivo .dot a .png automáticamente
    system("dot -Tpng reporteSolicitudes.dot -o reporteSolicitudes.png");
    system("start reporteSolicitudes.png");
}

bool SolicitudList::eliminarPorEmisorYReceptor(const string& emisor, const string& receptor) {
    if (head == nullptr) {
        return false; // Lista vacía
    }

    // Si el nodo a eliminar es el primero
    if (head->emisor == emisor && head->receptor == receptor) {
        SolicitudNode* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    SolicitudNode* current = head;
    while (current->next != nullptr) {
        if (current->next->emisor == emisor && current->next->receptor == receptor) {
            SolicitudNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        current = current->next;
    }
    return false; // Solicitud no encontrada
}
