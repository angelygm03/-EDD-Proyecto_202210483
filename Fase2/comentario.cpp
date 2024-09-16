#include "comentario.h"

// Constructor
Comentario::Comentario(string correo, string comentario, string fecha, string hora) {
    this->correo = correo;
    this->comentario = comentario;
    this->fecha = fecha;
    this->hora = hora;
}

// Método para comparar comentarios por fecha y hora
bool Comentario::compararFechaYHora(Comentario* otro) {
    if (fecha == otro->fecha)
        return hora < otro->hora;
    return fecha < otro->fecha;
}

// Método para imprimir el comentario
void Comentario::mostrarComentario() {
    cout << "Correo: " << correo << ", Comentario: " << comentario
         << ", Fecha: " << fecha << ", Hora: " << hora << endl;
}
