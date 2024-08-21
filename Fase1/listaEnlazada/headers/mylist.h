#ifndef MYLIST_H
#define MYLIST_H

#include "node.h"
#include "../../solicitudList/headers/solicitudList.h"

// Clase lista enlazada simple
class MyList {
private:
    Node* head; // Puntero al primer nodo de la lista
    int size;   // Tamaño de la lista (número de nodos)

public:
    // Constructor de la lista, inicializa la cabeza como nula y el tamaño en 0
    MyList();

    // Método para insertar un nuevo nodo en la lista
    void insert(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena);

    // Método para imprimir todos los nodos en la lista
    void print();

    // Método para buscar un nodo por su correo electrónico
    Node* buscar(const string& correo);

    // Método para eliminar un nodo por su correo electrónico
    bool eliminar(const string& correo);

    // Método para manejar las solicitudes pendientes
    void manejarSolicitudes(Node* usuario);

    // Método para generar el archivo dot
    void generateDotFile();

    // Método para las solicitudes pendientes
    SolicitudList& getSolicitudList();

    // Método para agregar una solicitud a la lista simple del emisor
    void agregarSolicitudEnviada(const string& emisor, const string& receptor);

    // Método para generar el archivo dot de las solicitudes enviadas
    void generateSolicitudDotFile(Node* usuario);

};

#endif
