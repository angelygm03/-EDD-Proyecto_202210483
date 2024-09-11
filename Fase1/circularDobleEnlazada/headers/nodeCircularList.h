#ifndef NODECIRCULARLIST_H
#define NODECIRCULARLIST_H

#include <iostream>
#include <string>
using namespace std;

class NodeCircularList {
public:
    string correo;
    string contenido;
    string fecha;
    string hora;

    NodeCircularList* next;
    NodeCircularList* prev;

    NodeCircularList(); // Constructor por defecto
    NodeCircularList(string correo, string contenido, string fecha, string hora); // Constructor parametrizado

    void print();
};

#endif