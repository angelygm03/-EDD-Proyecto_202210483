#include "headers/nodeCircularList.h"

NodeCircularList::NodeCircularList() {
    correo = "";
    contenido = "";
    fecha = "";
    hora = "";
    next = this;
    prev = this;
}

NodeCircularList::NodeCircularList(string correo, string contenido, string fecha, string hora) {
    this->correo = correo;
    this->contenido = contenido;
    this->fecha = fecha;
    this->hora = hora;
    next = this;
    prev = this;
}

void NodeCircularList::print() {
    cout << "----------------------------------------" << endl;
    cout << "Correo: " << correo << endl;
    cout << "Contenido: " << contenido << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "----------------------------------------" << endl;
}
