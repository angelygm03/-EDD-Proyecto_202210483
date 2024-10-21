#include "fechalist.h"
#include <iostream>

FechaList::FechaList() {
    head = nullptr;
}

void FechaList::agregarPublicacion(string correo, string contenido, string hora) {
    FechaNodo* nuevaPublicacion = new FechaNodo(correo, contenido, hora);

    if (head == nullptr) {
        head = nuevaPublicacion;
    } else {
        // Insertar al final de la lista
        FechaNodo* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nuevaPublicacion;
    }
}

void FechaList::imprimirPublicaciones() const {
    if (head == nullptr) {
        cout << "No hay publicaciones para esta fecha." << endl;
        return;
    }

    FechaNodo* temp = head;
    while (temp != nullptr) {
        cout << "Correo: " << temp->correo << endl;
        cout << "Contenido: " << temp->contenido << endl;
        cout << "Hora: " << temp->hora << endl;
        cout << "-------------------------------" << endl;
        temp = temp->next;
    }
}

