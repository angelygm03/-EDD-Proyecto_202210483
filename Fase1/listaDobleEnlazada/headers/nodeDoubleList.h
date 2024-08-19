#ifndef nodeDoubleList
#define nodeDoubleList

#include <iostream>
#include <string>
using namespace std;

// Clase que representa un nodo en la lista doblemente enlazada
class NodeDoubleList {
public:
    string correo;
    string contenido;
    string fecha;
    string hora;

    NodeDoubleList* next;
    NodeDoubleList* prev;

    NodeDoubleList(); // Constructor por defecto
    NodeDoubleList(string correo, string contenido, string fecha, string hora); // Constructor parametrizado

    void print(); // Método para imprimir la información del nodo
};

#endif