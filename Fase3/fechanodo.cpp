#include "fechanodo.h"

FechaNodo::FechaNodo(string correo, string contenido, string hora) {
    this->correo = correo;
    this->contenido = contenido;
    this->hora = hora;
    next = nullptr;
}

