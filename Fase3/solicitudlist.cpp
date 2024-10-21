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
