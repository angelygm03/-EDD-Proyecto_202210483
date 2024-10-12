#ifndef FECHALIST_H
#define FECHALIST_H

#include "fechanodo.h"
using namespace std;

// Clase para manejar la lista simplemente enlazada de publicaciones de una fecha específica
class FechaList {
private:

public:
    FechaNodo* head;
    FechaList();  // Constructor
    void agregarPublicacion(string correo, string contenido, string hora);
    void imprimirPublicaciones() const;
};

#endif // FECHALIST_H
