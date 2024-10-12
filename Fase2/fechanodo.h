#ifndef FECHANODO_H
#define FECHANODO_H

#include <string>
using namespace std;

class FechaNodo {
public:
    string correo;  // Correo del usuario que hizo la publicación
    string contenido;  // Contenido de la publicación
    string hora;  // Hora de la publicación
    FechaNodo* next;

    // Constructor
    FechaNodo(string correo, string contenido, string hora);
};

#endif // FECHANODO_H
