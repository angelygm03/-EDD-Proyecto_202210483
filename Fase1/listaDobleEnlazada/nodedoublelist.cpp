#include "headers/nodeDoubleList.h"

// Constructor por defecto
NodeDoubleList::NodeDoubleList() {
    correo = "";
    contenido = "";
    fecha = "";
    hora = "";
    next = nullptr;
    prev = nullptr;
}

// Constructor parametrizado
NodeDoubleList::NodeDoubleList(string correo, string contenido, string fecha, string hora) {
    this->correo = correo;
    this->contenido = contenido;
    this->fecha = fecha;
    this->hora = hora;
    next = nullptr;
    prev = nullptr;
}

// Método para imprimir la información del nodo
void NodeDoubleList::print() {
    cout << "----------------------------------------" << endl;
    cout << "Correo: " << correo << endl;
    cout << "Contenido: " << contenido << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "----------------------------------------" << endl;
}