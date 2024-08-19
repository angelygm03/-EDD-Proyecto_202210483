#include "headers/doublelist.h"

// Constructor
DoubleList::DoubleList() : head(nullptr), tail(nullptr), size(0) {}

// Método para insertar al principio de la lista doblemente enlazada
void DoubleList::insertAtBeginning(string correo, string contenido, string fecha, string hora) {
    NodeDoubleList* newNode = new NodeDoubleList(correo, contenido, fecha, hora);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    size++;
}

// Inserta una publicación al final de la lista
void DoubleList::insertAtEnd(const string& correo, const string& contenido, const string& fecha, const string& hora) {
    NodeDoubleList* newNode = new NodeDoubleList(correo, contenido, fecha, hora);

    if (tail == nullptr) { // Si la lista está vacía
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Inserta una publicación en una posición específica
void DoubleList::insertAtPosition(int givenPosition, string correo, string contenido, string fecha, string hora) {
    if (givenPosition <= 0) {
        insertAtBeginning(correo, contenido, fecha, hora);
    } else if (givenPosition >= size) {
        insertAtEnd(correo, contenido, fecha, hora);
    } else {
        NodeDoubleList* newNode = new NodeDoubleList(correo, contenido, fecha, hora);
        NodeDoubleList* current = head;
        for (int actualPosition = 0; actualPosition < givenPosition - 1; actualPosition++) {
            current = current->next;
        }

        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;

        size++;
    }
}

// Imprime la lista completa
void DoubleList::print() const {
    if (head == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    NodeDoubleList* current = head;
    int position = 0;
    while (current != nullptr) {
        cout << "ID " << position << ": ";
        current->print();
        current = current->next;
        position++;
    }
}

// Elimina una publicación por su ID (position)
bool DoubleList::deleteAtPosition(int position) {
    if (position < 0 || position >= size) {
        return false;
    }

    NodeDoubleList* current = head;
    for (int actualPosition = 0; actualPosition < position; actualPosition++) {
        current = current->next;
    }

    if (current == head) {
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else if (current == tail) {
        tail = current->prev;
        tail->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    size--;
    return true;
}

//Método para imprimir las publicaciones de un usuario específico
void DoubleList::printByUser(const string& correoUsuario) const {
    if (head == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    NodeDoubleList* current = head;
    int position = 0;
    while (current != nullptr) {
        if (current->correo == correoUsuario) {
            cout << "ID " << position << ": ";
            current->print();
        }
        current = current->next;
        position++;
    }
}

//Método para eliminar las publicaciones de un usuario específico
bool DoubleList::deleteByUser(int position, const string& correoUsuario) {
    if (position < 0 || position >= size) {
        return false;
    }

    NodeDoubleList* current = head;
    for (int actualPosition = 0; actualPosition < position; actualPosition++) {
        current = current->next;
    }

    if (current->correo != correoUsuario) {
        return false; // La publicación no pertenece al usuario
    }

    // Eliminar el nodo
    if (current == head) {
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else if (current == tail) {
        tail = current->prev;
        tail->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    size--;
    return true;
}

