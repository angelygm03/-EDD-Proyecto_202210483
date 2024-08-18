#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
using namespace std;

// Clase que representa un nodo en la lista enlazada
class Node {
public:
    string nombres;         
    string apellidos;       
    string fechaNacimiento; 
    string correo;          
    string contrasena;      
    Node* next;             

    // Constructores del nodo
    Node();
    Node(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena);

    // Método para imprimir la información del nodo
    void print();
};

#endif