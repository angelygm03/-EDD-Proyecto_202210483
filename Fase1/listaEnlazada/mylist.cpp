#include "headers/mylist.h"

// Constructor inicializa la cabeza de la lista como nula y el tamaño en 0
MyList::MyList() : head(nullptr), size(0) {}

// Método para insertar un nuevo nodo al final de la lista
void MyList::insert(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena) {
    // Crear un nuevo nodo con los datos
    Node* newNode = new Node(nombres, apellidos, fechaNacimiento, correo, contrasena);

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (head == nullptr) {
        head = newNode;
    } else {
        // De lo contrario, recorrer la lista hasta el último nodo
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // Conectar el último nodo con el nuevo nodo
        current->next = newNode;
    }
    size++; // Incrementar el tamaño de la lista
}

// Método para imprimir todos los nodos de la lista
void MyList::print() {
    // Si la lista está vacía, imprimir un mensaje y salir
    if (head == nullptr) {
        cout << "No hay usuarios en la lista." << endl;
        return;
    }

    // Recorrer la lista e imprimir la información de cada nodo
    Node* current = head;
    while (current != nullptr) {
        current->print();
        current = current->next;
    }
}
