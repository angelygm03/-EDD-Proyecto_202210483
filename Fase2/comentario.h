#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <iostream>
using namespace std;

class Comentario {
public:
    string correo;
    string comentario;
    string fecha;
    string hora;

    // Constructor del comentario
    Comentario(string correo, string comentario, string fecha, string hora);

    // Método para comparar las fechas y horas de los comentarios
    bool compararFechaYHora(Comentario* otro);
    void mostrarComentario();
};

#endif // COMENTARIO_H
